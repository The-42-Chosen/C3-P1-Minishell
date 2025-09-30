/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 19:01:32 by erpascua          #+#    #+#             */
/*   Updated: 2025/09/30 18:27:20 by erpascua         ###   ########.fr       */
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

int	bi_echo(t_msh *msh, char **av)
{
	int		i;
	bool	no_newline;

	i = 1;
	no_newline = false;
	while (av[i] && is_flag_n(av[i]))
	{
		no_newline = true;
		i++;
	}
	while (av[i])
	{
		ft_fprintf(1, "%s", av[i]);
		i++;
		if (av[i])
			ft_fprintf(1, " ");
	}
	if (!no_newline)
		ft_fprintf(1, "\n");
	msh->exit_code = 0;
	return (0);
}
