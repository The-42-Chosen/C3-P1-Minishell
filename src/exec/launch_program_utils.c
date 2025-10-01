/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_program_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 20:31:22 by erpascua          #+#    #+#             */
/*   Updated: 2025/10/01 20:33:16 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_signals(t_msh *msh)
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

char	*clean_entry(char *entry)
{
	char	*res;

	if (!entry)
		return (NULL);
	res = ft_strtrim(entry, " \f\t\n\r\v");
	free(entry);
	return (res);
}
