/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_eof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:31:59 by erpascua          #+#    #+#             */
/*   Updated: 2025/08/14 18:42:08 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_eof(void)
{
	if (isatty(STDIN_FILENO))
	{
		ft_putendl_fd("exit", 1);
		return (true);
	}
	return (false);
}
