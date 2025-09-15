/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 09:11:35 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/15 18:42:37 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	get_env_var_len(char *word)
{
	size_t	i;

	if (!word)
		return (0);
	i = 0;
	while (word[i] && word[i] != ' ' && word[i] != '$')
	{
		i++;
	}
	return (i);
}

char	*my_getenv(t_msh *msh, char *word)
{
	int	i;
	int	len;
	
	i = 0;
	len = get_env_var_len(word + 1);
	while (msh->env[i])
	{
		if (!ft_strncmp(msh->env[i], word + 1, len) && msh->env[i][len] == '=')
		{
			return (msh->env[i] + len + 1);
		}	
		i++;
	}
	return (NULL);
}

void	print_lst(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		ft_fprintf(1, "lst : %s|\n", tmp->content);
		tmp = tmp->next;
	}
}

t_list	*split_env_var(char *s)
{
	t_list	*lst;
	char	*content;
	char	*var_ptr;
	char	*ptr;
	
	lst = NULL;
	ptr = s;
	while (*ptr)
	{
		var_ptr = ft_strchr(ptr, '$');
		if (var_ptr)
		{
			content = ft_substr(ptr, 0, var_ptr - ptr);
			ft_lstadd_back(&lst, ft_lstnew(content));
			content = ft_substr(var_ptr, 0, get_env_var_len(var_ptr + 1) + 1);
			ptr = var_ptr + get_env_var_len(var_ptr + 1) + 1;
		}
		else
		{
			content = ft_substr(ptr, 0, ft_strlen(ptr));
			ptr = ptr + ft_strlen(ptr);
		}
		ft_lstadd_back(&lst, ft_lstnew(content));
	}
	return (lst);
}

char	*replace_env_var(t_msh *msh, char *s)
{
	char	*tmp;

	if (s[0] == '$')
	{
		if (s[0] == '$')
		{
			if (my_getenv(msh, s))
			{
				tmp = s;
				s = ft_strdup(my_getenv(msh, s));
				free(tmp);
			}
			else
			{
				tmp = s;
				s = ft_strdup("");		
				free(tmp);
			}
		}
	}
	return (s);
}

char	*expand(t_msh *msh, char *s)
{
	char	*res;
	char	*tmp;
	// char	*env_str;
	t_list	*lst;
	
	if (!s)
		return (NULL);
	res = malloc(sizeof(char));
	res[0] = 0;
	lst = split_env_var(s);
	while (lst)
	{
		tmp = res;
		lst->content = replace_env_var(msh, ((char *)lst->content));
		res = ft_strjoin(res, lst->content);
		free(tmp);
		lst = lst->next;
	}
	ft_lstclear(&lst, free);
	return (res);
}
