/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:18:27 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/23 15:34:48 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmd_copy(t_data *data, t_cmd *copy)
{
	ft_memcpy(copy, &data->cmd, sizeof(t_cmd)); 
	if (data->cmd.path)
	{
		copy->path = ft_strdup(data->cmd.path);
		if (!copy->path)
			return (0);
	}
	copy->args = string_array_copy(data->cmd.args);
	if (!copy->args)
		return (0);
	return (1);
}

t_process	*pre_exec(t_msh *msh)
{
	t_data		*data;
	t_process	*process;
	t_process	*head;

	data = msh->data;
	process = calloc(1, sizeof(t_process));
	if (!process)
		return (NULL);
	head = process;
	while (data)
	{
		if (data->group == G_CMD)
		{
			if (!cmd_copy(data, &head->cmd))
				return (NULL);
		}
		if (data->group == G_PIPE)
		{
			ft_lstadd_back(&head->outputs, ft_lstnew(alloc_pipe_inout()));
			head->next = calloc(1, sizeof(t_process));
			head = head->next;
			ft_lstadd_back(&head->inputs, ft_lstnew(alloc_pipe_inout()));
		}
		data = data->next;
	}
	head = process;
	data = msh->data;
	while (data)
	{
		if (data->group == G_REDIR_IN || data->group == G_REDIR_HEREDOC)
			ft_lstadd_back(&head->inputs, ft_lstnew(alloc_redir_inout(data)));
		if (data->group == G_REDIR_OUT || data->group == G_REDIR_APPEND)
			ft_lstadd_back(&head->outputs, ft_lstnew(alloc_redir_inout(data)));
		if (data->group == G_PIPE)
			head = head->next;
		data = data->next;
	}
	return (process);
}
