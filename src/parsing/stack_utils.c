/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:10:00 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/01 15:01:40 by gpollast         ###   ########.fr       */
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

int	add_word_to_stack(t_msh *msh, char *word)
{
	t_stack	*tmp;

	if (!msh->stack)
	{
		msh->stack = new_stack(word);
		if (!msh->stack)
			return (0);
		if (msh->is_append == true)
			msh->stack->is_append = true;
		msh->stack->is_expandable = msh->is_expandable;
	}
	else
	{
		tmp = new_stack(word);
		if (!tmp)
			return (0);
		if (msh->is_append == true)
			tmp->is_append = true;
		tmp->is_expandable = msh->is_expandable;
		stack_add_back(&msh->stack, tmp);
	}
	return (1);
}

t_stack	*copy_node_stack(t_stack *stack, char *s)
{
	t_stack	*copy;

	copy = (t_stack *)ft_calloc(1, sizeof(*copy));
	if (!copy)
		return (NULL);
	if (s)
	{
		copy->content = ft_strdup(s);
		if (!copy->content)
		{
			free(copy);
			return (NULL);
		}
	}
	copy->sub_token = stack->sub_token;
	copy->token = stack->token;
	copy->next = NULL;
	return (copy);
}
