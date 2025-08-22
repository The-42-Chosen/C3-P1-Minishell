/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:37:31 by erpascua          #+#    #+#             */
/*   Updated: 2025/08/22 11:48:09 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

void	update_history(t_msh *msh)
{
	add_history(msh->entry);
	append_history(1, msh->history);
}

void	repl(t_msh *msh, int tmp_fd)
{
	char	*entry;
	char	*entry_no_nl;
	int		tmp_fd;

	tmp_fd = open("tmp_fd", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp_fd < 0)
		return (perror("open"), 1);
	repl(msh, tmp_fd);
	close(tmp_fd);
	unlink("tmp_fd");
	return (0);
}
