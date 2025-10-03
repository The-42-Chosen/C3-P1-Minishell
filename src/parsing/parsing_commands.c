/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:00:00 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/03 16:26:58 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_concatenation(char *s, char *content)
{
	char	*tmp_s;

	if (!s)
		return (ft_strjoin("", content));
	tmp_s = s;
	s = ft_strjoin(s, content);
	free(tmp_s);
	return (s);
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
		{
			s = handle_concatenation(s, tmp->next->content);
			if (tmp->next->is_append == false)
			{
				stack_add_back(&new, copy_node_stack(tmp, s));
				free(s);
				s = NULL;
				tmp = tmp->next;
			}
		}
		else
			stack_add_back(&new, copy_node_stack(tmp, tmp->content));
		tmp = tmp->next;
	}
	return (new);
}

int	add_command_node(t_msh *msh, t_stack **tmp, t_data *new_node,
		t_stack **head)
{
	new_node->cmd.args = seek_group_cmd(msh, tmp, head);
	if (!new_node->cmd.args)
		return (0);
	new_node->group = G_CMD;
	new_node->cmd.builtin_type = get_builtin_type(msh, new_node);
	if (new_node->cmd.builtin_type == BI_NONE)
		set_up_path(msh, new_node);
	return (1);
}
