/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_part_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:29:39 by erpascua          #+#    #+#             */
/*   Updated: 2025/10/02 10:20:30 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
