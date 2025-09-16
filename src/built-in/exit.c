/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ep <ep@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:34:10 by erpascua          #+#    #+#             */
/*   Updated: 2025/09/16 09:30:45 by ep               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_code_nb(char *str)
{
	int	j;

	j = 0;
	if (str[j] == '+' || str[j] == '-')
		j++;
	while (str[j])
	{
		if (!ft_isdigit(str[j]))
			return (false);
		j++;
	}
	return (true);
}

int	bi_exit(char **argv)
{
	int	argc;

	argc = 0;
	ft_putendl_fd("exit", 1);
	while (argv[argc])
		argc++;
	if (argc >= 2)
	{
		if (!is_valid_code_nb(argv[1]))
		{
			ft_fprintf(2, "minishell: exit: %s: numeric argument required\n",
				argv[1]);
			g_exit_code = 255;
			exit(g_exit_code);
		}
		g_exit_code = ((ft_atoi(argv[1]) % 256) + 256) % 256;
	}
	if (argc > 2)
	{
		ft_fprintf(2, "minishell: exit: too many arguments\n");
		g_exit_code = 1;
		exit(1);
	}
	exit(g_exit_code);
}
