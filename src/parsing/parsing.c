/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:53:38 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/01 16:33:37 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	err_next_token(t_stack *stack, t_token t)
{
	if (stack->token == t)
	{
		if (stack->next->token == t)
		{
			g_exit_code = 2;
			ft_fprintf(2, "bash: syntax error near unexpected token `%s'\n",
				stack->next->content);
			return (1);
		}
	}
	return (0);
}

int	parse(t_msh *msh)
{
	t_stack	*tmp;

	tmp = msh->stack;
	while (tmp && tmp->next)
	{
		if (err_next_token(tmp, REDIR) || err_next_token(tmp, OPERATOR))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
