/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:37:31 by erpascua          #+#    #+#             */
/*   Updated: 2025/10/02 10:20:19 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	launch_exec(t_msh *msh, t_process **process)
{
	signal(SIGINT, sigint_silent_handler);
	signal(SIGQUIT, sigquit_handler);
	execute_all(msh, *process);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	free_process(*process);
}

static void	cleanup_loop_data(t_msh *msh)
{
	if (msh->data)
		data_destroy(msh->data);
	msh->data = NULL;
	msh->stack = NULL;
	msh->nb_cmd = 0;
	free(msh->entry);
	msh->entry = NULL;
}

static int	repl(t_msh *msh)
{
	t_process	*process;

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
		if (!msh->entry)
			break ;
		if (reloop(msh, &process))
			launch_exec(msh, &process);
		cleanup_loop_data(msh);
		if (msh->has_to_exit)
			break ;
	}
	if (!isatty(STDOUT_FILENO))
		close(STDOUT_FILENO);
	return (1);
}

int	launch_program(t_msh *msh)
{
	int	result;

	read_history(msh->history);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
	result = repl(msh);
	if (result)
	{
		free(msh->history);
		return (0);
	}
	free(msh->history);
	return (1);
}
