/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:00:00 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/01 20:04:17 by erpascua         ###   ########.fr       */
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

static char	**setup_cmd(t_msh *msh, t_stack *stack, int nb_cmd)
{
	char	**group;
	t_stack	*tmp;
	int		i;

	group = calloc((nb_cmd + 1), sizeof(char *));
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

int	set_up_path(t_msh *msh, t_data *data)
{
	data->cmd.path = cmd_path(msh, data->cmd.args[0]);
	return (1);
}
