/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:00:26 by erpascua          #+#    #+#             */
/*   Updated: 2025/10/02 19:26:35 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_banner_lines(void)
{
	static char	*banner[] = {
		"                                                                     ",
		"█████   █████  █     █     █     █ █████ █   █ █████ █     █         ",
		"██  ██    █    █     █      █   █  █     █   █ █     █     █         ",
		"█████     █    █     █       ███   █████ █████ ███   █     █         ",
		"██  ██    █    █     █        █        █ █   █ █     █     █         ",
		"█████   █████  █████ █████    █    █████ █   █ █████ █████ █████     ",
		"                                                                     ",
		"                                                                     ",
		NULL
	};

	return (banner);
}

static const char	**get_banner_colors(void)
{
	static const char	*colors[] = {
		"\033[31m",
		"\033[93m",
		"\033[32m",
		"\033[36m",
		"\033[34m",
		"\033[38;5;93m",
	};

	return (colors);
}

static void	print_banner_line(char *line, int l_idx, const char **colors)
{
	if (l_idx == 0 || !line)
	{
		ft_fprintf(1, "\033[97m%s\n", line);
		return ;
	}
	ft_fprintf(1, "%s%s\n", colors[(l_idx - 1) % 6], line);
}

void	print_banner(void)
{
	char		**banner;
	const char	**colors;
	int			i;

	if (!isatty(STDOUT_FILENO) || !isatty(STDIN_FILENO)
		|| getenv("MS_NO_BANNER"))
		return ;
	banner = get_banner_lines();
	colors = get_banner_colors();
	write(STDOUT_FILENO, "\033[3J\033[2J\033[H", 10);
	i = 0;
	while (banner[i])
	{
		print_banner_line(banner[i], i, colors);
		i++;
	}
	write(STDOUT_FILENO, "\033[0m", 4);
}
