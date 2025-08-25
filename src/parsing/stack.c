/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:43:16 by gpollast          #+#    #+#             */
/*   Updated: 2025/08/25 19:08:31 by gpollast         ###   ########.fr       */
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
