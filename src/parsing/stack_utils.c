/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:10:00 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/26 14:38:52 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_stack(t_stack *s)
{
	t_stack	*tmp;

	tmp = s;
	while (tmp)
	{
		ft_fprintf(1, "%s", tmp->content);
		if (tmp->token == WORD)
			ft_fprintf(1, " WORD\n");
		else if (tmp->token == REDIR)
			ft_fprintf(1, " REDIR\n");
		else if (tmp->token == PIPE)
			ft_fprintf(1, " PIPE\n");
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

t_stack	*copy_node_stack(t_stack *stack, char *s)
{
	t_stack	*copy;

	copy = new_stack(s);
	if (!copy)
        return (NULL);
	copy->is_append = stack->is_append;
	copy->is_expandable = stack->is_expandable;
	copy->sub_token = stack->sub_token;
	copy->token = stack->token;
	copy->next = NULL;
	return (copy);
}
