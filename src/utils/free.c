/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 16:34:38 by erpascua          #+#    #+#             */
/*   Updated: 2025/09/29 02:27:57 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_destroy(t_env *env)
{
	t_env	*tmp;
	t_env	*next;

	while (env)
	{
		tmp = env;
		next = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		env = next;
	}
}

void	free_msh(t_msh *msh)
{
	free_data(msh->data);
	free(msh->entry);
	free(msh->history);
	stack_destroy(msh->stack);
	env_destroy(msh->env);
}

void	free_msh_builtins(t_msh *msh)
{
	int	i;

	i = 0;
	while (i < NB_BUILTINS)
	{
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
	free(cmd->path);
}

void	free_data(t_data *data)
{
	t_data	*tmp;
	t_data	*next;

	while (data)
	{
		tmp = data;
		next = data->next;
		free_cmd(&tmp->cmd);
		free(tmp->file_or_limiter);
		free(tmp);
		data = next;
	}
}

void	free_process(t_process *process)
{
	t_process	*tmp;
	t_process	*next;

	while (process)
	{
		tmp = process;
		next = process->next;
		free_cmd(&tmp->cmd);
		ft_lstclear(&tmp->inputs, free_inout);
		ft_lstclear(&tmp->outputs, free_inout);
		free(tmp);
		process = next;
	}
}

void	free_inout(void *content)
{
	t_inout	*inout;

	if (!content)
		return ;
	inout = (t_inout *)content;
	free(inout->file_or_limiter);
	free(inout);
}

