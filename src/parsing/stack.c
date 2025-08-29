/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:43:16 by gpollast          #+#    #+#             */
/*   Updated: 2025/08/29 11:55:33 by gpollast         ###   ########.fr       */
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
	new->token = NULL;
	new->sub_token = NULL;
    new->next = NULL;
    return (new);
}

static  t_stack *stack_last(t_stack *s)
{
	while (s)
	{
		if (s -> next != 0)
			s = s -> next;
		if (s -> next == 0)
			return (s);
	}
	return (NULL);
}

void	stack_add_back(t_stack **s, t_stack *new)
{
	if (!s || !new)
		return ;
	if (*s == NULL)
	{
		*s = new;
		return ;
	}
	else
		stack_last(*s)->next = new;
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
