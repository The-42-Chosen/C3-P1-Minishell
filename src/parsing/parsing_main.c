/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:00:00 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/19 11:33:23 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_next_token_for_redir(t_stack *stack, t_token t)
{
	if (stack->token == t)
	{
		if (stack->next && stack->next->token == t)
		{
			g_exit_code = 2;
			ft_fprintf(2, "bash: syntax error near unexpected token `%s'\n",
				stack->next->content);
			return (1);
		}
	}
	return (0);
}

static int	add_node(t_msh *msh, t_stack **tmp)
{
	t_data	*new_node;

	new_node = init_data_node();
	if (!new_node)
		return (0);
	if ((*tmp)->token == REDIR)
	{
		if (!add_redir_node(tmp, new_node))
		{
			data_destroy(new_node);
			return (0);
		}
	}
	else if ((*tmp)->token == WORD)
	{
		if (!add_command_node(tmp, new_node))
		{
			data_destroy(new_node);
			return (0);
		}
	}
	else if ((*tmp)->token == PIPE)
		new_node->group = G_PIPE;
	msh->data = data_add_back((msh->data), new_node);
	return (1);
}

int	parse(t_msh *msh)
{
	t_stack	*tmp;

	tmp = msh->stack;
	while (tmp)
	{
		if (check_next_token_for_redir(tmp, REDIR))
			return (0);
		if (!add_node(msh, &tmp))
			return (0);
		tmp = tmp->next;
	}
	set_up_path(msh);
	return (1);
}
