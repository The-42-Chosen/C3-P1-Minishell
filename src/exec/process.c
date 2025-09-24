/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 13:50:26 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/24 15:08:17 by gpollast         ###   ########.fr       */
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
	if (lst->next)
		close(inout->fd);
	if (inout->unused_fd)
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

	if (access(process->cmd.path, X_OK) == -1)
	{
		ft_fprintf(2, "Billyshell: %s: command not found\n", process->cmd.args[0]);
		msh->exit_code = 127;
		return (0);
	}
	pid = fork();
	if (pid == 0)
	{
		ft_lstiter(process->inputs, (void (*)(void *))dup_all_read);
		ft_lstiter(process->outputs, (void (*)(void *))dup_all_write);
		cleanup_inout_fds(process->inputs);
		cleanup_inout_fds(process->outputs);
		execve(process->cmd.path, process->cmd.args, msh_getenv(msh));
	}
	return (pid);
}

static int	open_input(t_list *input)
{
	t_inout	*in;
	int		fds[2];
	char	*line;
	
	if (!input)
		return (1);
	in = (t_inout *)input->content;
	if (in->type == G_REDIR_IN)
	{
		in->fd = open(in->file_or_limiter, O_RDONLY);
		if (in->fd == -1)
		{
			ft_fprintf(2, "Billyshell: %s: No such file or directory\n", in->file_or_limiter);
			return (0);
		}
	}
	if (in->type == G_REDIR_HEREDOC)
	{
		if (pipe(fds) == -1)
			return (0);
		line = readline("> ");
		while (ft_strncmp(line, in->file_or_limiter, ft_strlen(in->file_or_limiter)))
		{
			write(fds[1], line, ft_strlen(line));
			write(fds[1], "\n", 1);
			free(line);
			line = readline("> ");
		}
		close(fds[1]);
		in->fd = fds[0];
	}
	return (open_input(input->next));
}

static int	open_output(t_list *output, t_list *next_process_input)
{
	t_inout	*out;
	t_inout	*npi;
	int		flag;
	int		fds[2];
	
	if (!output)
		return (1);
	out = (t_inout *)output->content;
	if (out->type == G_REDIR_OUT || out->type == G_REDIR_APPEND)
	{
		flag = O_CREAT | O_WRONLY;
		flag |= (out->type == G_REDIR_OUT) ? O_TRUNC : O_APPEND;
		out->fd = open(out->file_or_limiter, flag, 0644);
		if (out->fd == -1)
		{
			ft_fprintf(2, "Billyshell: %s: No such file or directory\n", out->file_or_limiter);
			return (0);
		}
	}
	if (out->type == G_PIPE)
	{
		if (pipe(fds) == -1)
			return (0);
		npi = (t_inout *)next_process_input->content;
		npi->fd = fds[0];
		npi->unused_fd = fds[1];
		out->fd = fds[1];
		out->unused_fd = fds[0];
	}
	return (open_output(output->next, next_process_input));
}

static void	execute(t_msh *msh, t_process *process)
{
	int	cin;
	int	cout;
	
	if (!process)
		return ;
	if (!open_input(process->inputs))
		return ;
	if (process->next)
		open_output(process->outputs, process->next->inputs);
	else
		open_output(process->outputs, NULL);
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
	}
	ft_lstiter(process->inputs, (void (*)(void *))close_inout);
	ft_lstiter(process->outputs, (void (*)(void *))close_inout);
	execute(msh, process->next);
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
