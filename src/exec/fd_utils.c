/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:40:00 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/02 16:46:20 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_inout_fds(t_list *lst)
{
	t_inout	*inout;

	if (!lst)
		return ;
	inout = lst->content;
	close(inout->fd);
	close(inout->unused_fd);
	cleanup_inout_fds(lst->next);
}

void	close_inout(t_inout *inout)
{
	if (inout->fd > 1)
		close(inout->fd);
}

void	dup_all_read(t_inout *inout)
{
	if (inout->fd > 0)
		dup2(inout->fd, 0);
}

void	dup_all_write(t_inout *inout)
{
	if (inout->fd > 1)
		dup2(inout->fd, 1);
}