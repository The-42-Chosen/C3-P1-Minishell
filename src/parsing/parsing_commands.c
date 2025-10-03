/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:00:00 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/03 11:08:03 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_nb_cmd(t_stack **stack)
{
	int		nb_cmd;
	t_stack	*tmp;

	nb_cmd = 0;
	tmp = *stack;
	while (tmp && tmp->token == WORD)
	{
		nb_cmd++;
		tmp = tmp->next;
	}
	return (nb_cmd);
}

t_stack	*concatenate_stack(t_stack *stack)
{
	t_stack	*tmp;
	t_stack	*new;
	char	*tmp_s;
	char	*s;

	new = NULL;
	s = NULL;
	tmp_s = NULL;
	tmp = stack;
	while (tmp)
	{
		if (tmp->is_append == true && tmp->next)
		{
			if (!s)
				s = ft_strjoin(tmp->content, tmp->next->content);
			else
			{
				tmp_s = s;
				s = ft_strjoin(s, tmp->next->content);
				free(tmp_s);
			}
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

static char	**setup_cmd(t_msh *msh, t_stack *stack, int nb_cmd)
{
	char	**group;
	t_stack	*tmp;
	int		i;

	group = ft_calloc((nb_cmd + 1), sizeof(char *));
	if (!group)
		return (msh->exit_code = 12, NULL);
	tmp = stack;
	i = 0;
	while (i < nb_cmd && tmp)
	{
		group[i] = ft_strdup(tmp->content);
		if (!group[i])
		{
			while (--i >= 0)
				free(group[i]);
			free(group);
			msh->exit_code = 12;
			return (NULL);
		}
		i++;
		tmp = tmp->next;
	}
	return (group);
}

static char	**seek_group_cmd(t_msh *msh, t_stack **stack, t_stack **head)
{
	int		nb_cmd;
	char	**group;
	int		i;

	*stack = concatenate_stack(*stack);
	stack_destroy(*head);
	*head = *stack;
	nb_cmd = count_nb_cmd(stack);
	group = setup_cmd(msh, *stack, nb_cmd);
	if (!group)
		return (NULL);
	i = 0;
	while (i < nb_cmd - 1)
	{
		*stack = (*stack)->next;
		i++;
	}
	return (group);
}

int	add_command_node(t_msh *msh, t_stack **tmp,
		t_data *new_node, t_stack **head)
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

int	set_up_path(t_msh *msh, t_data *data)
{
	data->cmd.path = cmd_path(msh, data->cmd.args[0]);
	return (1);
}
