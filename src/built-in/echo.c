/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 19:01:32 by erpascua          #+#    #+#             */
/*   Updated: 2025/09/12 20:15:37 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_flag_n(char *s)
{
	int	i;

	if (!s || !s[0] != '-' || s[1] != 'n')
		return (false);
	i = 2;
	while (s[i])
	{
		if (s[i] != 'n')
			return (true);
		i++;
	}
	return (true);
}

int	bi_echo(char **argv)
{
	int		i;
	bool	no_newline;
	bool	is_first;

	i = 1;
	no_newline = false;
	is_first = true;
	while (argv[i] && is_flag_n(argv[i]))
	{
		no_newline = true;
		i++;
	}
	while (argv[i])
	{
		ft_fprintf(1, "%s", argv[i]);
		if (is_first)
		{
			ft_fprintf(1, " ");
			is_first = false;
		}
		i++;
	}
	if (!no_newline)
		ft_fprintf(1, "\n");
	return (0);
}
