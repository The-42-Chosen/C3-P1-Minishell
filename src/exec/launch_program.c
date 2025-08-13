/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:37:31 by erpascua          #+#    #+#             */
/*   Updated: 2025/08/22 11:53:08 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch_program(void)
{
	char	*entry;
	int		tmp_fd;

	read_history(msh->history);
	tmp_fd = open("tmp_fd", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp_fd < 0)
		return (perror("open"), 1);
	while (1)
	{
		write(1, "\033[1;92mMinishell > \033[0m", 23);
		entry = get_next_line(0);
		if (!entry)
			break ;
		else
		{
			update_history(msh, entry);
			is_builtin(msh, entry);
		}
		write(tmp_fd, entry, ft_strlen(entry));
		free(entry);
		free(entry_no_nl);
	}
	close(tmp_fd);
	free(msh->history);
	unlink("tmp_fd");
	return (0);
}
