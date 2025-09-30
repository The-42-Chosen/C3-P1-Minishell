/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:37:31 by erpascua          #+#    #+#             */
/*   Updated: 2025/09/30 19:20:17 by gpollast         ###   ########.fr       */
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
	{
		if (msh->stack)
			stack_destroy(msh->stack);
		return (0);
	}
	if (!parse(msh))
	{
		return (0);
	}
	*process = pre_exec(msh);
	return (1);
}

static char	*clean_entry(char *entry)
{
	char	*res;

	if (!entry)
		return (NULL);
	res = ft_strtrim(entry, " \f\t\n\r\v");
	free(entry);
	return (res);
}

static int	repl(t_msh *msh)
{
	t_process	*process;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
	while (1)
	{
		check_signals(msh);
		if (isatty(STDOUT_FILENO))
			msh->entry = readline("\033[1;92mBillyshell > \033[0m");
		else
			msh->entry = get_next_line(0);
		if (!msh->entry && is_eof())
			break ;
		update_history(msh);
		msh->entry = clean_entry(msh->entry);
		if (!msh->entry) // DON'T TOUCH
			break ;
		if (reloop(msh, &process))
		{
			signal(SIGINT, sigint_silent_handler);
			execute_all(msh, process);
			signal(SIGINT, sigint_handler);
			free_process(process);
		}
		if (msh->data)
			free_data(msh->data);
		msh->data = NULL;
		msh->stack = NULL;
		msh->nb_cmd = 0;
		free(msh->entry);
	}
	if (!isatty(STDOUT_FILENO))
		close(STDOUT_FILENO);
	return (1);
}

int	launch_program(t_msh *msh)
{
	int	result;

	read_history(msh->history);
	result = repl(msh);
	if (result)
	{
		free(msh->history);
		return (0);
	}
	free(msh->history);
	return (1);
}
