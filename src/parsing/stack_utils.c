/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:10:00 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/25 15:43:09 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_stack(t_stack *s)
{
	t_stack	*tmp;

	tmp = s;
	while (tmp)
	{
		ft_fprintf(1, "%s\n", tmp->content);
		tmp = tmp->next;
	}
}

void	add_word_to_stack(t_msh *msh, char *word)
{
	t_stack	*tmp;

	if (!msh->stack)
	{
		msh->stack = new_stack(word);
	}
	else
	{
		tmp = new_stack(word);
		if (msh->is_append == true)
			tmp->is_append = true;
		msh->stack->is_expandable = msh->is_expandable;
		stack_add_back(&msh->stack, tmp);
	}
}
