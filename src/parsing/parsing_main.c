/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:00:00 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/24 18:35:58 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_next_token_for_redir(t_msh *msh, t_stack *stack, t_token t)
{
	if (stack->token == t)
	{
		if (stack->next && stack->next->token == t)
		{
			msh->exit_code = 2;
			ft_fprintf(2, "Billyshell: syntax error near unexpected token `%s'\n",
				stack->next->content);
			return (0);
		}
	}
	return (1);
}

static int	add_node(t_msh *msh, t_stack **tmp)
{
	t_data	*new_node;

	new_node = init_data_node(msh);
	if (!new_node)
		return (0);
	if ((*tmp)->token == REDIR)
	{
		if (!add_redir_node(msh, tmp, new_node))
		{
			data_destroy(new_node);
			return (0);
		}
	}
	else if ((*tmp)->token == WORD)
	{
		if (!add_command_node(msh, tmp, new_node))
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

static int	count_nb_cmd(t_data *data)
{
	t_data	*tmp;
	int		nb_cmd;

	tmp = data;
	nb_cmd = 0;
	while (tmp)
	{
		if (tmp->group == G_CMD)
			nb_cmd++;
		tmp = tmp->next;
	}
	return (nb_cmd);
}

int	parse(t_msh *msh)
{
	t_stack	*tmp;
	// t_data	*tmp2;

	tmp = msh->stack;
	while (tmp)
	{
		if (!check_next_token_for_redir(msh, tmp, REDIR))
			return (0);
		if (!add_node(msh, &tmp))
			return (0);
		tmp = tmp->next;
	}
	msh->nb_cmd = count_nb_cmd(msh->data);
	// tmp2 = msh->data;
	// while (tmp2)
	// {
	// 	if (tmp2->group == G_REDIR_IN)
	// 		ft_fprintf(1, "REDIR_IN\n");
	// 	if (tmp2->group == G_REDIR_OUT)
	// 		ft_fprintf(1, "REDIR_OUT\n");
	// 	if (tmp2->group == G_REDIR_APPEND)
	// 		ft_fprintf(1, "REDIR_APPEND\n");
	// 	if (tmp2->group == G_REDIR_HEREDOC)
	// 		ft_fprintf(1, "REDIR_HEREDOC\n");
	// 	if (tmp2->group == G_PIPE)
	// 		ft_fprintf(1, "PIPE\n");
	// 	if (tmp2->group == G_CMD)
	// 	{
	// 		if (tmp2->cmd.builtin_type == BI_NONE)
	// 			ft_fprintf(1, "PATH: %s ", tmp2->cmd.path);
	// 		ft_fprintf(1, "CMD: ");
	// 		print_string_array(tmp2->cmd.args);
	// 	}
	// 	tmp2 = tmp2->next;
	// }
	return (1);
}
