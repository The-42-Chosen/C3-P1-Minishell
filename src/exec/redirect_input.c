/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:37:19 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/02 17:22:54 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

static void	heredoc_child(t_msh *msh, t_inout *in, t_process *process, int *fds)
{
	char	*line;

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

static int	handle_heredoc(t_msh *msh, t_inout *in, t_process *process)
{
	int		fds[2];
	pid_t	pid;
	int		status;

	if (pipe(fds) == -1)
	{
		msh->exit_code = 1;
		return (0);
	}
	pid = fork();
	if (pid == 0)
		heredoc_child(msh, in, process, fds);
	waitpid(pid, &status, 0);
	if (status == 139)
		ft_fprintf(2,
			"Billyshell: warning: here-document at current line delimited "
			"by end-of-file (wanted `%s')\n\n",
			in->file_or_limiter);
	close(fds[1]);
	in->fd = fds[0];
	if (status > 0)
		return (0);
	return (1);
}

static int	handle_file_input(t_msh *msh, t_inout *in)
{
	in->fd = open(in->file_or_limiter, O_RDONLY);
	if (in->fd == -1)
	{
		ft_fprintf(2, "Billyshell: %s: No such file or directory\n",
			in->file_or_limiter);
		msh->exit_code = 1;
		return (0);
	}
	return (1);
}

int	open_input(t_msh *msh, t_list *input, t_process *process)
{
	t_inout	*in;

	if (!input)
		return (1);
	in = (t_inout *)input->content;
	if (in->type == G_REDIR_IN)
	{
		if (!handle_file_input(msh, in))
			return (0);
	}
	else if (in->type == G_REDIR_HEREDOC)
	{
		if (!handle_heredoc(msh, in, process))
			return (0);
	}
	return (open_input(msh, input->next, process));
}
