/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 09:11:35 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/29 02:36:08 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*add_content_to_list(t_list **lst, char *content)
{
	t_list	*new_node;

	if (!content)
		return (ft_lstclear(lst, free), NULL);
	new_node = ft_lstnew(content);
	if (!new_node)
		return (ft_lstclear(lst, free), free(content), NULL);
	ft_lstadd_back(lst, new_node);
	return (*lst);
}

static t_list	*process_var(t_list **lst, char **ptr)
{
	char	*content;
	char	*var_ptr;
	size_t	var_len;

	var_ptr = ft_strchr(*ptr, '$');
	content = ft_substr(*ptr, 0, var_ptr - *ptr);
	if (!add_content_to_list(lst, content))
		return (NULL);
	var_len = get_env_var_len(var_ptr + 1);
	content = ft_substr(var_ptr, 0, var_len + 1);
	if (!add_content_to_list(lst, content))
		return (NULL);
	*ptr = var_ptr + var_len + 1;
	return (*lst);
}

t_list	*split_env_var(char *s)
{
	t_list	*lst;
	char	*content;
	char	*ptr;

	lst = NULL;
	ptr = s;
	while (*ptr)
	{
		if (ft_strchr(ptr, '$'))
		{
			if (!process_var(&lst, &ptr))
				return (ft_lstclear(&lst, free), NULL);
		}
		else
		{
			content = ft_substr(ptr, 0, ft_strlen(ptr));
			if (!add_content_to_list(&lst, content))
				return (ft_lstclear(&lst, free), NULL);
			ptr = ptr + ft_strlen(ptr);
		}
	}
	return (lst);
}

char	*replace_env_var(t_msh *msh, char *s)
{
	char	*tmp;

	if (s[0] == '$')
	{
		if (s[1] == '?' && s[2] == 0)
		{
			tmp = s;
			s = ft_strdup(ft_itoa(msh->exit_code));
			free(tmp);
		}
		else if (my_getenv(msh, s))
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
	return (s);
}

char	*expand(t_msh *msh, char *s)
{
	char	*res;
	char	*tmp;
	t_list	*lst;
	t_list	*current;

	if (!s)
		return (NULL);
	res = malloc(sizeof(char));
	if (!res)
		return (NULL);
	res[0] = 0;
	lst = split_env_var(s);
	current = lst;
	while (current)
	{
		tmp = res;
		current->content = replace_env_var(msh, ((char *)current->content));
		res = ft_strjoin(res, current->content);
		if (!res)
			return (ft_lstclear(&lst, free), free(tmp), NULL);
		free(tmp);
		current = current->next;
	}
	ft_lstclear(&lst, free);
	return (res);
}
