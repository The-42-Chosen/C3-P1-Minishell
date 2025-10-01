/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:18:27 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/01 17:17:10 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmd_copy(t_data *data, t_cmd *copy)
{
	char	**tmp;

	tmp = NULL;
	if (!copy->args)
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
	}
	else
	{
		tmp = copy->args;
		copy->args = string_array_concat(copy->args, data->cmd.args);
		free_tab(tmp);
	}
	return (1);
}

static t_process	*create_processes(t_msh *msh)
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
		if (data->group == G_CMD && !cmd_copy(data, &head->cmd))
			return (NULL);
		if (data->group == G_PIPE)
		{
			ft_lstadd_back(&head->outputs, ft_lstnew(alloc_pipe_inout()));
			head->next = calloc(1, sizeof(t_process));
			head = head->next;
			ft_lstadd_back(&head->inputs, ft_lstnew(alloc_pipe_inout()));
		}
		data = data->next;
	}
	return (process);
}

static void	add_redirections(t_process *process, t_msh *msh)
{
	t_data		*data;
	t_process	*head;

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
}

t_process	*pre_exec(t_msh *msh)
{
	t_process	*process;

	process = create_processes(msh);
	if (!process)
		return (NULL);
	add_redirections(process, msh);
	return (process);
}
