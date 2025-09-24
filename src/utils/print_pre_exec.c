/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pre_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:16:53 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/23 14:59:59 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_pre_exec(t_process *process)
{
	t_process	*tmp;

	tmp = process;
	while (tmp)
	{
		if (tmp->cmd.args)
			ft_fprintf(1, "CMD: %s\n", tmp->cmd.args[0]);
		ft_fprintf(1, "Inputs:\n");
		ft_lstiter(tmp->inputs, (void (*)(void *))print_inout);
		ft_fprintf(1, "\n");
		ft_fprintf(1, "Outputs:\n");
		ft_lstiter(tmp->outputs, (void (*)(void *))print_inout);
		ft_fprintf(1, "\n");
		tmp = tmp->next;
	}
}
