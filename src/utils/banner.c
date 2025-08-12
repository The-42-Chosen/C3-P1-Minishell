/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:00:26 by erpascua          #+#    #+#             */
/*   Updated: 2025/08/12 15:52:39 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* clang-format off */
static char	**get_banner_lines(void)
{
	static char	*banner[] = {
		"                                                                     ",
		"██████  ██ ██      ██    ██ ███████ ██   ██ ███████ ██      ██       ",
		"██   ██ ██ ██       ██  ██  ██      ██   ██ ██      ██      ██       ",
		"██████  ██ ██        ████   ███████ ███████ █████   ██      ██       ",
		"██   ██ ██ ██         ██         ██ ██   ██ ██      ██      ██       ",
		"██████  ██ ███████    ██    ███████ ██   ██ ███████ ███████ ███████  ",
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
/* clang-format on */

static void	print_banner_line(char *line, int l_idx, const char **colors)
{
	if (l_idx == 0 || !line)
	{
		dprintf(STDOUT_FILENO, "\033[97m");
		ft_putendl_fd(line, STDOUT_FILENO);
		return ;
	}
	dprintf(STDOUT_FILENO, "%s", colors[(l_idx - 1) % 6]);
	ft_putendl_fd(line, STDOUT_FILENO);
}

void	print_banner(void)
{
	char		**banner;
	const char	**colors;
	int			i;

	if (!isatty(STDOUT_FILENO) || getenv("MS_NO_BANNER"))
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
