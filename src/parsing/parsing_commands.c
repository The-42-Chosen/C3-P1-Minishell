/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:00:00 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/20 18:42:05 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

static char	**setup_cmd(t_stack *stack, int nb_cmd)
{
	char	**group;
	t_stack	*tmp;
	int		i;

	group = calloc((nb_cmd + 1), sizeof(char *));
	if (!group)
		return (g_exit_code = 12, NULL);
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
			g_exit_code = 12;
			return (NULL);
		}
		i++;
		tmp = tmp->next;
	}
	return (group);
}

static char	**seek_group_cmd(t_stack **stack)
{
	int		nb_cmd;
	char	**group;
	int		i;

	nb_cmd = count_nb_cmd(stack);
	group = setup_cmd(*stack, nb_cmd);
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

int	add_command_node(t_stack **tmp, t_data *new_node)
{
	new_node->cmd.args = seek_group_cmd(tmp);
	if (!new_node->cmd.args)
		return (0);
	new_node->group = G_CMD;
	return (1);
}

int	set_up_path(t_msh *msh)
{
	t_data	*tmp;

	tmp = msh->data;
	while (tmp)
	{
		if (tmp->group == G_CMD)
			tmp->cmd.path = cmd_path(msh, tmp->cmd.args[0]);
		tmp = tmp->next;
	}
	return (1);
}
