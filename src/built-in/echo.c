/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ep <ep@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 19:01:32 by erpascua          #+#    #+#             */
/*   Updated: 2025/09/16 07:34:21 by ep               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_flag_n(char *s)
{
	int	i;

	if (!s || s[0] != '-' || s[1] != 'n')
		return (false);
	i = 2;
	while (s[i])
	{
		if (s[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	bi_echo(char **argv)
{
	int		i;
	bool	no_newline;

	i = 1;
	no_newline = false;
	while (argv[i] && is_flag_n(argv[i]))
	{
		no_newline = true;
		i++;
	}
	while (argv[i])
	{
		ft_fprintf(1, "%s", argv[i]);
		i++;
		if (argv[i])
			ft_fprintf(1, " ");
	}
	if (!no_newline)
		ft_fprintf(1, "\n");
	return (0);
}
