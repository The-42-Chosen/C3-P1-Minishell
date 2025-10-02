/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 13:50:26 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/02 15:50:16 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

static void	cleanup_inout_fds(t_list *lst)
{
	t_inout	*inout;

	if (!lst)
		return ;
	inout = lst->content;
	close(inout->fd);
	close(inout->unused_fd);
	cleanup_inout_fds(lst->next);
}

static void	close_inout(t_inout *inout)
{
	if (inout->fd > 1)
		close(inout->fd);
}

static void	dup_all_read(t_inout *inout)
{
	if (inout->fd > 0)
		dup2(inout->fd, 0);
}

static void	dup_all_write(t_inout *inout)
{
	if (inout->fd > 1)
		dup2(inout->fd, 1);
}

static pid_t	execute_cmd(t_msh *msh, t_process *process)
{
	pid_t	pid;

	if (!process->cmd.path || access(process->cmd.path, X_OK) == -1)
	{
		if (!process->cmd.args)
			return (0);
		ft_fprintf(2, "Billyshell: %s: command not found\n",
			process->cmd.args[0]);
		msh->exit_code = 127;
		return (0);
	}
	pid = fork();
	if (pid == -1)
		return (msh->exit_code = 1, 0);
	if (pid == 0)
	{
		ft_lstiter(process->inputs, (void (*)(void *))dup_all_read);
		ft_lstiter(process->outputs, (void (*)(void *))dup_all_write);
		cleanup_inout_fds(process->inputs);
		cleanup_inout_fds(process->outputs);
		execve(process->cmd.path, process->cmd.args, msh_getenv(msh));
		exit(msh->exit_code);
	}
	return (pid);
}

static int	open_input(t_msh *msh, t_list *input, t_process *process)
{
	t_inout	*in;
	int		fds[2];
	char	*line;
	pid_t	pid;
	int		status;

	if (!input)
		return (1);
	in = (t_inout *)input->content;
	if (in->type == G_REDIR_IN)
	{
		in->fd = open(in->file_or_limiter, O_RDONLY);
		if (in->fd == -1)
		{
			ft_fprintf(2, "Billyshell: %s: No such file or directory\n",
				in->file_or_limiter);
			msh->exit_code = 1;
			return (0);
		}
	}
	if (in->type == G_REDIR_HEREDOC)
	{
		if (pipe(fds) == -1)
		{
			msh->exit_code = 1;
			return (0);
		}
		pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			line = readline("> ");
			while (ft_strcmp(line, in->file_or_limiter))
			{
				line = expand(msh, line);
				write(fds[1], line, ft_strlen(line));
				write(fds[1], "\n", 1);
				free(line);
				line = readline("> ");
			}
			ft_lstiter(process->inputs, (void (*)(void *))close_inout);
			ft_lstiter(process->outputs, (void (*)(void *))close_inout);
			free_msh(msh);
			free_msh_builtins(msh);
			free_process(process);
			close(fds[0]);
			close(fds[1]);
			exit(0);
		}
		waitpid(pid, &status, 0);
		if (status == 139)
			ft_fprintf(2,
				"Billyshell: warning: here-document at current line delimited by end-of-file (wanted `%s')\n\n",
				in->file_or_limiter);
		close(fds[1]);
		in->fd = fds[0];
		if (status > 0)
			return (0);
	}
	return (open_input(msh, input->next, process));
}

static void	execute(t_msh *msh, t_process *process)
{
	int	cin;
	int	cout;

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
	{
		cin = dup(0);
		cout = dup(1);
		ft_lstiter(process->inputs, (void (*)(void *))dup_all_read);
		ft_lstiter(process->outputs, (void (*)(void *))dup_all_write);
		execute_builtin(msh, process);
		dup2(cin, 0);
		dup2(cout, 1);
		close(cin);
		close(cout);
	}
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
