/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:43:16 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/01 18:23:37 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	stack_destroy(t_stack *head)
{
	if (!head)
		return ;
	stack_destroy(head->next);
	free(head);
}

t_stack	*new_stack(char *content)
{
	t_stack	*new;

	new = malloc(sizeof(t_stack));
	if (!new)
		return (NULL);
	new->content = ft_strdup(content);
	if (!new->content)
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

static t_stack	*stack_last(t_stack *s)
{
	if (!s)
		return (NULL);
	while (s->next)
		s = s->next;
	return (s);
}

void	stack_add_back(t_stack **s, t_stack *new_s)
{
	if (!s || !new_s)
		return ;
	if (*s == NULL)
	{
		*s = new_s;
		return ;
	}
	else
		stack_last(*s)->next = new_s;
}

int	fill_stack(t_stack **s, char *word)
{
	t_stack	*new;

	new = new_stack(word);
	if (!new)
		return (0);
	new->next = *s;
	*s = new;
	return (1);
}
