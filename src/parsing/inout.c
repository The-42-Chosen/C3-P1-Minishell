/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:34:12 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/03 11:08:03 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_inout(t_inout *inout)
{
	if (inout->type == G_PIPE)
		ft_fprintf(1, "PIPE\n");
	else if (inout->type == G_REDIR_IN)
		ft_fprintf(1, "REDIR IN File: %s\n", inout->file_or_limiter);
	else if (inout->type == G_REDIR_HEREDOC)
		ft_fprintf(1, "REDIR HEREDOC Limiter: %s\n", inout->file_or_limiter);
	else if (inout->type == G_REDIR_OUT)
		ft_fprintf(1, "REDIR OUT File: %s\n", inout->file_or_limiter);
	else if (inout->type == G_REDIR_APPEND)
		ft_fprintf(1, "REDIR APPEND File: %s\n", inout->file_or_limiter);
}

t_inout	*alloc_pipe_inout(void)
{
	t_inout	*res;

	res = ft_calloc(1, sizeof(*res));
	if (!res)
		return (NULL);
	res->type = G_PIPE;
	return (res);
}

t_inout	*alloc_redir_inout(t_data *data)
{
	t_inout	*res;

	res = ft_calloc(1, sizeof(*res));
	if (!res)
		return (NULL);
	res->file_or_limiter = ft_strdup(data->file_or_limiter);
	if (!res->file_or_limiter)
		return (free(res), NULL);
	res->type = data->group;
	return (res);
}
