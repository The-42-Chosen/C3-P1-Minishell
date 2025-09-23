/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 13:50:26 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/23 16:54:01 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

static pid_t	execute_cmd(t_msh *msh, t_process *process)
{
	pid_t	pid;

	if (access(process->cmd.path, X_OK) == -1)
	{
		ft_fprintf(2, "billyshell: %s: command not found\n", process->cmd.args[0]);
		msh->exit_code = 127;
		return (0);
	}
	pid = fork();
	if (pid == 0)
	{
		// dup2(0, 0);
		execve(process->cmd.path, process->cmd.args, msh_getenv(msh));
	}
	return (pid);
}

static void	execute(t_msh *msh, t_process *process)
{
	if (process->cmd.builtin_type == BI_NONE)
		process->pid = execute_cmd(msh, process);
	else
		execute_builtin(msh, process);
	// execute(msh, process->next);
}

void	execute_all(t_msh *msh, t_process *process)
{
	t_process	*head;
	
	execute(msh, process);
	head = process;
	while (head)
	{
		if (head->pid)
			waitpid(head->pid, &msh->exit_code, 0);
		head = head->next;
	}
}
