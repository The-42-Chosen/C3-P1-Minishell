/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:00:00 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/22 11:07:23 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_data	*init_data_node(t_msh *msh)
{
	t_data	*new_node;

	new_node = malloc(sizeof(t_data));
	if (!new_node)
	{
		msh->exit_code = 12;
		return (NULL);
	}
	ft_memset(new_node, 0, sizeof(*new_node));
	return (new_node);
}

static t_data	*data_last(t_data *data)
{
	while (data)
	{
		if (data->next != 0)
			data = data->next;
		if (data->next == 0)
			return (data);
	}
	return (NULL);
}

t_data	*data_add_back(t_data *data, t_data *new)
{
	if (!new)
		return (data);
	if (data == NULL)
		return (new);
	else
		data_last(data)->next = new;
	return (data);
}

void	data_destroy(t_data *head)
{
	if (!head)
		return ;
	data_destroy(head->next);
	if (head->cmd.args)
		free_tab(head->cmd.args);
	if (head->cmd.path)
		free(head->cmd.path);
	if (head->file_or_limiter)
		free(head->file_or_limiter);
	free(head);
}
