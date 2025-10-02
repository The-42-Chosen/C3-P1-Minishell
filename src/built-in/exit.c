/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:34:10 by erpascua          #+#    #+#             */
/*   Updated: 2025/10/02 01:04:06 by ubuntu           ###   ########.fr       */
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

void	clean_exit(t_msh *msh, char *s)
{
	ft_fprintf(2, "Billyshell: exit: %s: numeric argument required\n", s);
	msh->exit_code = 255;
	msh->has_to_exit = true;
}

int	bi_exit(t_msh *msh, char **argv)
{
	int	argc;

	// if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
	// 	return (0);
	argc = 0;
	ft_putendl_fd("exit", 1);
	while (argv[argc])
		argc++;
	if (argc >= 2)
	{
		if (!is_valid_code_nb(argv[1]))
			return (clean_exit(msh, argv[1]), 0);
		if (is_overflow(argv[1]))
			return (clean_exit(msh, argv[1]), 0);
		else
			msh->exit_code = ft_atoi(argv[1]) % 256;
	}
	if (argc > 2)
	{
		ft_fprintf(2, "Billyshell: exit: too many arguments\n");
		msh->exit_code = 1;
		return (0);
	}
	msh->has_to_exit = true;
	return (0);
}
