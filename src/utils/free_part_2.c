/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_part_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:29:39 by erpascua          #+#    #+#             */
/*   Updated: 2025/09/30 14:50:51 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_data(t_data *data)
{
	t_data	*tmp;
	t_data	*next;

	while (data)
	{
		tmp = data;
		next = data->next;
		free_cmd(&tmp->cmd);
		if (tmp->file_or_limiter)
			free(tmp->file_or_limiter);
		free(tmp);
		data = next;
	}
}

void	free_process(t_process *process)
{
	t_process	*tmp;
	t_process	*next;

	while (process)
	{
		tmp = process;
		next = process->next;
		free_cmd(&tmp->cmd);
		if (tmp->inputs)
			ft_lstclear(&tmp->inputs, free_inout);
		if (tmp->outputs)
			ft_lstclear(&tmp->outputs, free_inout);
		free(tmp);
		process = next;
	}
}

void	free_inout(void *content)
{
	t_inout	*inout;

	if (!content)
		return ;
	inout = (t_inout *)content;
	if (inout->file_or_limiter)
		free(inout->file_or_limiter);
	free(inout);
}
