/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_commands_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 20:03:20 by erpascua          #+#    #+#             */
/*   Updated: 2025/10/01 20:03:57 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*join_content(char *s, char *new_content)
{
	char	*tmp_s;
	char	*result;

	if (!s)
		return (ft_strjoin("", new_content));
	tmp_s = s;
	result = ft_strjoin(s, new_content);
	free(tmp_s);
	return (result);
}

static t_stack	*handle_append_node(t_stack **new, t_stack *tmp, char **s)
{
	*s = join_content(*s, tmp->next->content);
	if (!*s)
		return (NULL);
	if (tmp->next->is_append == false)
	{
		stack_add_back(new, copy_node_stack(tmp, *s));
		free(*s);
		*s = NULL;
		return (tmp->next);
	}
	return (tmp);
}

t_stack	*concatenate_stack(t_stack *stack)
{
	t_stack	*tmp;
	t_stack	*new;
	char	*s;

	new = NULL;
	s = NULL;
	tmp = stack;
	while (tmp)
	{
		if (tmp->is_append == true && tmp->next)
			tmp = handle_append_node(&new, tmp, &s);
		else
			stack_add_back(&new, copy_node_stack(tmp, tmp->content));
		if (!tmp)
			break ;
		tmp = tmp->next;
	}
	return (new);
}
