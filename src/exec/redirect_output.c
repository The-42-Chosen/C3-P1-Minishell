/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:54:23 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/01 18:04:34 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_file_output(t_msh *msh, t_inout *out)
{
	if (out->type == G_REDIR_OUT)
		out->fd = open(out->file_or_limiter, O_CREAT | O_WRONLY | O_TRUNC,
				0644);
	else
		out->fd = open(out->file_or_limiter, O_CREAT | O_WRONLY | O_APPEND,
				0644);
	if (out->fd == -1)
	{
		ft_fprintf(2, "Billyshell: %s: No such file or directory\n",
			out->file_or_limiter);
		msh->exit_code = 1;
		return (0);
	}
	return (1);
}

static int	handle_pipe_output(t_msh *msh, t_inout *out,
		t_list *next_process_input)
{
	t_inout	*npi;
	int		fds[2];

	if (pipe(fds) == -1)
	{
		msh->exit_code = 1;
		return (0);
	}
	npi = (t_inout *)next_process_input->content;
	npi->fd = fds[0];
	npi->unused_fd = fds[1];
	out->fd = fds[1];
	out->unused_fd = fds[0];
	return (1);
}

int	open_output(t_msh *msh, t_list *output, t_list *next_process_input)
{
	t_inout	*out;

	if (!output)
		return (1);
	out = (t_inout *)output->content;
	if (out->type == G_REDIR_OUT || out->type == G_REDIR_APPEND)
	{
		if (!handle_file_output(msh, out))
			return (0);
	}
	else if (out->type == G_PIPE)
	{
		if (!handle_pipe_output(msh, out, next_process_input))
			return (0);
	}
	return (open_output(msh, output->next, next_process_input));
}
