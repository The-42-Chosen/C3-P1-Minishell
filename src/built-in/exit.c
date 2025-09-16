/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ep <ep@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:34:10 by erpascua          #+#    #+#             */
/*   Updated: 2025/09/16 15:59:32 by ep               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_code_nb(char *str)
{
	int	j;

	j = 0;
	if (str[j] == '+' || str[j] == '-')
		j++;
	if (!str[j] || !ft_isdigit(str[j]))
		return (false);
	while (str[j])
	{
		if (!ft_isdigit(str[j]))
			return (false);
		j++;
	}
	return (true);
}

static bool	is_overflow(char *str)
{
	char	*int_max_str;
	char	*int_min_str;
	int		len;

	int_max_str = "9223372036854775807";
	int_min_str = "-9223372036854775808";
	len = ft_strlen(str);
	if (str[0] == '-' && len > 20)
		return (true);
	if (str[0] != '-' && len > 19)
		return (true);
	if (str[0] != '-' && len == 19 && ft_strncmp(str, int_max_str, 19) > 0)
		return (true);
	if (str[0] == '-' && len == 20 && ft_strncmp(str, int_min_str, 20) > 0)
		return (true);
	return (false);
}

void	clean_exit(char *s)
{
	ft_fprintf(2, "minishell: exit: %s: numeric argument required\n", s);
	g_exit_code = 255;
	exit(g_exit_code);
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
			clean_exit(argv[1]);
		if (is_overflow(argv[1]))
			clean_exit(argv[1]);
		else
			g_exit_code = ft_atoi(argv[1]) % 256;
	}
	if (argc > 2)
	{
		ft_fprintf(2, "minishell: exit: too many arguments\n");
		g_exit_code = 1;
		exit(1);
	}
	exit(g_exit_code);
}
