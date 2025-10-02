/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 13:50:26 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/02 17:22:05 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

static void	execute(t_msh *msh, t_process *process)
{
	if (!process)
		return ;
	if (!open_input(msh, process->inputs, process))
		return ;
	if (process->next)
	{
		if (!open_output(msh, process->outputs, process->next->inputs))
			return ;
	}
	else
	{
		if (!open_output(msh, process->outputs, NULL))
			return ;
	}
	if (process->cmd.builtin_type == BI_NONE)
		process->pid = execute_cmd(msh, process);
	else
		execute_builtin_process(msh, process);
	ft_lstiter(process->inputs, (void (*)(void *))close_inout);
	ft_lstiter(process->outputs, (void (*)(void *))close_inout);
	execute(msh, process->next);
}

void	execute_all(t_msh *msh, t_process *process)
{
	t_process	*head;
	int			status;

	execute(msh, process);
	head = process;
	while (head)
	{
		if (head->pid)
		{
			waitpid(head->pid, &status, 0);
			if (WIFEXITED(status))
				msh->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				msh->exit_code = 128 + WTERMSIG(status);
		}
		else
			msh->exit_code = head->bi_exit_code;
		head = head->next;
	}
}
