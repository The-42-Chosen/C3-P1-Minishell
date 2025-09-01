/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_classification.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:35:00 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/01 17:25:53 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redir_symbol(t_stack *s)
{
	if (s->content && (s->content[0] == '<' || s->content[0] == '>'))
		return (true);
	return (false);
}

bool	is_operation_symb(t_stack *s)
{
	if (s->content && (s->content[0] == '|' || s->content[0] == '&'))
		return (true);
	return (false);
}

void	handle_redirection_token(t_stack *tmp)
{
	if (is_valid_redir(tmp))
		tmp->token = REDIR;
	else
	{
		g_exit_code = 2;
		if (ft_strlen(tmp->content) == 3)
			ft_fprintf(2, "bash: syntax error near unexpected token `%c'\n",
				tmp->content[2]);
		else
			ft_fprintf(2, "bash: syntax error near unexpected token `%c%c'\n",
				tmp->content[2], tmp->content[3]);
	}
}

void	handle_operator_token(t_stack *tmp)
{
	if (is_valid_operator(tmp))
		tmp->token = OPERATOR;
	else
	{
		g_exit_code = 2;
		ft_fprintf(2, "bash: syntax error near unexpected token `%c'\n",
			tmp->content[0]);
	}
}

void	classify_single_token(t_stack *tmp)
{
	if (is_redir_symbol(tmp))
		handle_redirection_token(tmp);
	else if (is_valid_pipe(tmp))
		tmp->token = PIPE;
	else if (is_operation_symb(tmp))
		handle_operator_token(tmp);
	else
	{
		tmp->token = WORD;
		tmp->sub_token = NONE;
	}
}
