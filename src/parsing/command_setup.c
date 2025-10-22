/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:24:56 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/22 19:59:20 by gpollast         ###   ########.fr       */
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
		if (ft_strncmp(tmp->content, "", 1))
			nb_cmd++;
		tmp = tmp->next;
	}
	return (nb_cmd);
}

static int	count_nb_word(t_stack **stack)
{
	int		nb_word;
	t_stack	*tmp;

	nb_word = 0;
	tmp = *stack;
	while (tmp && tmp->token == WORD)
	{
		nb_word++;
		tmp = tmp->next;
	}
	return (nb_word);
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
		if (ft_strncmp(tmp->content, "", 1))
		{
			group[i] = ft_strdup(tmp->content);
			if (!group[i])
			{
				while (--i >= 0)
					free(group[i]);
				return (free(group), msh->exit_code = 12, NULL);
			}	
			i++;
		}
		tmp = tmp->next;
	}
	return (group);
}

char	**seek_group_cmd(t_msh *msh, t_stack **stack, t_stack **head)
{
	int		nb_cmd;
	char	**group;
	int		i;
	int		nb_word;

	*stack = concatenate_stack(*stack);
	stack_destroy(*head);
	*head = *stack;
	nb_cmd = count_nb_cmd(stack);
	if (!nb_cmd)
		return (NULL);
	group = setup_cmd(msh, *stack, nb_cmd);
	if (!group)
		return (NULL);
	i = 0;
	nb_word = count_nb_word(stack);
	while (i < (nb_word - 1))
	{
		*stack = (*stack)->next;
		i++;
	}
	return (group);
}

int	set_up_path(t_msh *msh, t_data *data)
{
	data->cmd.path = cmd_path(msh, data->cmd.args[0]);
	return (1);
}
