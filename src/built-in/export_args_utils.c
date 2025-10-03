/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_args_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 05:40:52 by ep                #+#    #+#             */
/*   Updated: 2025/10/03 12:44:11 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	export_replace_value(t_env *env, t_env *new_node)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, new_node->key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(new_node->value);
			if (!tmp->value)
				return (false);
			free(new_node->key);
			free(new_node->value);
			free(new_node);
			return (true);
		}
		tmp = tmp->next;
	}
	return (false);
}

t_env	*create_env_node_no_value(char *key)
{
	t_env	*new_node;

	if (!key || !*key)
		return (NULL);
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	if (!new_node->key)
		return (NULL);
	new_node->value = NULL;
	new_node->next = NULL;
	if (!new_node->key)
	{
		free(new_node);
		return (NULL);
	}
	return (new_node);
}

bool	export_replace_value_no_val(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (tmp->value)
			{
				free(tmp->value);
				tmp->value = NULL;
			}
			return (true);
		}
		tmp = tmp->next;
	}
	return (false);
}

void	export_create_keyvalue(t_msh *msh, t_env *new_node)
{
	t_env	*tmp;

	if (!msh->env)
	{
		msh->env = new_node;
		return ;
	}
	tmp = msh->env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

void	export_var_with_value(t_msh *msh, char *arg)
{
	t_env	*new_node;
	bool	is_found;

	new_node = create_env_node(arg);
	if (!new_node)
		return ;
	is_found = export_replace_value(msh->env, new_node);
	if (!is_found)
		export_create_keyvalue(msh, new_node);
}
