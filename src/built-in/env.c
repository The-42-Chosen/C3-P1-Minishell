/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 19:06:05 by erpascua          #+#    #+#             */
/*   Updated: 2025/09/26 16:31:03 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*safe_strdup_substr(const char *src, size_t len)
{
	char	*dst;

	dst = malloc(len + 1);
	if (!dst)
		return (NULL);
	ft_memcpy(dst, src, len);
	dst[len] = '\0';
	return (dst);
}

t_env	*create_env_node(char *env_line)
{
	char	*equal_pos;
	t_env	*new_node;

	if (!env_line)
		return (NULL);
	equal_pos = ft_strchr(env_line, '=');
	if (!equal_pos)
		return (NULL);
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = safe_strdup_substr(env_line, equal_pos - env_line);
	new_node->value = ft_strdup(equal_pos + 1);
	new_node->next = NULL;
	if (!new_node->key || !new_node->value)
	{
		free(new_node->key);
		free(new_node->value);
		free(new_node);
		return (NULL);
	}
	return (new_node);
}

static void	add_env_node(t_env **head, t_env **current, t_env *new_node)
{
	if (!*head)
	{
		*head = new_node;
		*current = new_node;
	}
	else
	{
		(*current)->next = new_node;
		*current = new_node;
	}
}

void	save_env(t_msh *msh, char **env)
{
	int		i;
	t_env	*new_node;
	t_env	*current;

	i = 0;
	msh->env = NULL;
	current = NULL;
	while (env[i])
	{
		new_node = create_env_node(env[i]);
		if (!new_node)
		{
			free_env_list(msh->env);
			msh->env = NULL;
			return ;
		}
		add_env_node(&msh->env, &current, new_node);
		i++;
	}
}

int	bi_env(t_msh *msh, char **av)
{
	t_env	*tmp;

	if (av[1] != NULL)
	{
		msh->exit_code = 127;
		ft_fprintf(2, "Billyshell: env: %s: No such file or directory\n",
			av[1]);
		return (msh->exit_code);
	}
	tmp = msh->env;
	while (tmp)
	{
		if (tmp->key && tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	msh->exit_code = 0;
	return (0);
}
