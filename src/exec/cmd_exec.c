/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:40:00 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/02 20:57:28 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

pid_t	execute_cmd(t_msh *msh, t_process *process)
{
	pid_t	pid;

	if (!process->cmd.path || access(process->cmd.path, X_OK) == -1)
	{
		if (!process->cmd.args)
			return (0);
		ft_fprintf(2, "Billyshell: %s: command not found\n",
			process->cmd.args[0]);
		msh->exit_code = 127;
		process->bi_exit_code = 127;
		return (0);
	}
	pid = fork();
	if (pid == -1)
		return (msh->exit_code = 1, 0);
	if (pid == 0)
	{
		(signal(SIGINT, SIG_DFL), signal(SIGQUIT, SIG_DFL));
		ft_lstiter(process->inputs, (void (*)(void *))dup_all_read);
		ft_lstiter(process->outputs, (void (*)(void *))dup_all_write);
		cleanup_inout_fds(process->inputs);
		cleanup_inout_fds(process->outputs);
		execve(process->cmd.path, process->cmd.args, msh_getenv(msh));
		exit(msh->exit_code);
	}
	return (pid);
}
