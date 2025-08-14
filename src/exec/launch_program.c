/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:37:31 by erpascua          #+#    #+#             */
/*   Updated: 2025/08/22 11:55:32 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_history(t_msh *msh, char *entry)
{
	add_history(entry);
	append_history(1, msh->history);
}

void	repl(t_msh *msh, int tmp_fd)
{
	char	*entry;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			entry = readline("\033[1;92mMinishell > \033[0m");
		else
			entry = get_next_line(0);
		if (!entry && is_eof())
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
}

int	launch_program(t_msh *msh)
{
	int	tmp_fd;

	read_history(msh->history);
	tmp_fd = open("tmp_fd", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp_fd < 0)
		return (perror("open"), 1);
	repl(msh, tmp_fd);
	close(tmp_fd);
	free(msh->history);
	unlink("tmp_fd");
	return (msh->last_status);
}
