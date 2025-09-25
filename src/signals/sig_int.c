/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 15:21:44 by erpascua          #+#    #+#             */
/*   Updated: 2025/09/25 22:53:10 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

void	sigint_handler(int signum)
{
	g_received_signal = signum;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_silent_handler(int signum)
{
	g_received_signal = signum;
	write(STDOUT_FILENO, "^C\n", 3);
	rl_replace_line("", 0);
}
