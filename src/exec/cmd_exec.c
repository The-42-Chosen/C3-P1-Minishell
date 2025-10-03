/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:40:00 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/03 00:12:48 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_a_directory(char *s)
{
	struct stat	path_stat;

	if (stat(s, &path_stat) != 0)
		return (false);
	return (S_ISDIR(path_stat.st_mode));
}

static int	directory_treatment(t_msh *msh, t_process *process)
{
	if (is_a_directory(process->cmd.path))
	{
		ft_fprintf(2, "Billyshell: %s: Is a directory\n",
			process->cmd.args[0]);
		process->bi_exit_code = 126;
		return (msh->exit_code = 126, 0);
	}
	if (access(process->cmd.path, F_OK) != 0)
	{
		ft_fprintf(2, "Billyshell: %s: No such file or directory\n",
			process->cmd.args[0]);
		process->bi_exit_code = 127;
		return (msh->exit_code = 127, 0);
	}
	if (access(process->cmd.path, X_OK) != 0)
	{
		ft_fprintf(2, "Billyshell: %s: Permission denied\n",
			process->cmd.args[0]);
		process->bi_exit_code = 126;
		return (msh->exit_code = 126, 0);
	}
	return (1);
}

static void	execute_child_process(t_msh *msh, t_process *process)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	ft_lstiter(process->inputs, (void (*)(void *))dup_all_read);
	ft_lstiter(process->outputs, (void (*)(void *))dup_all_write);
	cleanup_inout_fds(process->inputs);
	cleanup_inout_fds(process->outputs);
	execve(process->cmd.path, process->cmd.args, msh_getenv(msh));
	exit(msh->exit_code);
}

pid_t	execute_cmd(t_msh *msh, t_process *process)
{
	pid_t	pid;

	if (!process->cmd.path || access(process->cmd.path, X_OK) == -1)
	{
		if (!process->cmd.args)
			return (0);
		ft_fprintf(2, "Billyshell: %s: command not found\n",
			process->cmd.args[0]);
		process->bi_exit_code = 127;
		return (msh->exit_code = 127, 0);
	}
	if (!directory_treatment(msh, process))
		return (0);
	pid = fork();
	if (pid == -1)
		return (msh->exit_code = 1, 0);
	if (pid == 0)
		execute_child_process(msh, process);
	return (pid);
}
