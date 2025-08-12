/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:37:31 by erpascua          #+#    #+#             */
/*   Updated: 2025/08/12 20:01:38 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_history(t_msh *msh, char *entry)
{
	add_history(entry);
	append_history(1, msh->history);
}

int	launch_program(t_msh *msh)
{
	char	*entry;
	int		tmp_fd;

	read_history(msh->history);
	tmp_fd = open("tmp_fd", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp_fd < 0)
		return (perror("open"), 1);
	while (1)
	{
		if (isatty(0))
			entry = readline("\033[1;92mMinishell > \033[0m");
		else
			entry = get_next_line(0);
		if (!entry)
			break ;
		else
			update_history(msh, entry);
		write(tmp_fd, entry, ft_strlen(entry));
		free(entry);
	}
	close(tmp_fd);
	unlink("tmp_fd");
	return (0);
}
