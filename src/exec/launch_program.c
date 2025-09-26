/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ep <ep@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:37:31 by erpascua          #+#    #+#             */
/*   Updated: 2025/09/26 03:11:14 by ep               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_signals(t_msh *msh)
{
	if (g_received_signal == SIGINT)
	{
		msh->exit_code = 130;
		g_received_signal = 0;
	}
}

void	update_history(t_msh *msh)
{
	add_history(msh->entry);
	append_history(1, msh->history);
}

static int	reloop(t_msh *msh, t_process **process)
{
	if (!lexer(msh))
		return (0);
	if (!parse(msh))
		return (0);
	*process = pre_exec(msh);
	return (1);
}

static int	repl(t_msh *msh, int tmp_fd)
{
	t_process	*process;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
	while (1)
	{
		check_signals(msh);
		if (isatty(STDIN_FILENO))
			msh->entry = readline("\033[1;92mBillyshell > \033[0m");
		else
			msh->entry = get_next_line(0);
		if (!msh->entry && is_eof())
			break ;
		else
			update_history(msh);
		if (reloop(msh, &process))
		{
			signal(SIGINT, sigint_silent_handler);
			execute_all(msh, process);
			signal(SIGINT, sigint_handler);
		}
		msh->data = NULL;
		msh->stack = NULL;
		msh->nb_cmd = 0;
		write(tmp_fd, msh->entry, ft_strlen(msh->entry));
		write(tmp_fd, "\n", 1);
		free(msh->entry);
	}
	return (1);
}

int	launch_program(t_msh *msh)
{
	int	tmp_fd;

	read_history(msh->history);
	tmp_fd = open("tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp_fd < 0)
		return (perror("open"), 1);
	if (repl(msh, tmp_fd))
		return (0);
	close(tmp_fd);
	free(msh->history);
	unlink("tmp");
	return (1);
}
