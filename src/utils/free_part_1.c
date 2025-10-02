/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_part_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:57:21 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/02 09:57:25 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_null(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
}

void	env_destroy(t_env *env)
{
	t_env	*tmp;
	t_env	*next;

	while (env)
	{
		tmp = env;
		next = env->next;
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
		env = next;
	}
}

void	free_msh(t_msh *msh)
{
	if (!msh)
		return ;
	if (msh->data)
		data_destroy(msh->data);
	if (msh->entry)
		free(msh->entry);
	if (msh->history)
		free(msh->history);
	if (msh->stack)
		stack_destroy(msh->stack);
	if (msh->env)
		env_destroy(msh->env);
}

void	free_msh_builtins(t_msh *msh)
{
	int	i;

	if (!msh)
		return ;
	i = 0;
	while (i < NB_BUILTINS)
	{
		if (msh->builtin_names[i])
			free(msh->builtin_names[i]);
		i++;
	}
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->args)
		free_tab(cmd->args);
	if (cmd->path)
		free(cmd->path);
}
