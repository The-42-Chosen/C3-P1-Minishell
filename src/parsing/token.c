/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:11:56 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/01 14:06:20 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_redir(t_stack *s)
{
	if (!s || !s->content)
		return (false);
	if (!ft_strncmp(s->content, "<<", 2) && ft_strlen(s->content) == 2)
	{
		s->sub_token = HEREDOC;
		return (true);
	}
	else if (!ft_strncmp(s->content, ">>", 2) && ft_strlen(s->content) == 2)
	{
		s->sub_token = APPEND;
		return (true);
	}
	else if (!ft_strncmp(s->content, "<", 1) && ft_strlen(s->content) == 1)
	{
		s->sub_token = IN;
		return (true);
	}
	else if (!ft_strncmp(s->content, ">", 1) && ft_strlen(s->content) == 1)
	{
		s->sub_token = OUT;
		return (true);
	}
	return (false);
}

bool	is_redir_symbol(t_stack *s)
{
	if (s->content[0] == '<' || s->content[0] == '>')
		return (true);
	return (false);
}

bool	is_operation_symb(t_stack *s)
{
	if (s->content[0] == '|' || s->content[0] == '&')
		return (true);
	return (false);
}

bool	is_valid_operator(t_stack *s)
{
	if (!s || !s->content)
		return (false);
	if (!ft_strncmp(s->content, "&&", 2) && ft_strlen(s->content) == 2)
	{
		s->sub_token = AND;
		return (true);
	}
	else if (!ft_strncmp(s->content, "||", 2) && ft_strlen(s->content) == 2)
	{
		s->sub_token = OR;
		return (true);
	}
	return (false);
}

bool	is_valid_pipe(t_stack *s)
{
	if (!s || !s->content)
		return (false);
	if (!ft_strncmp(s->content, "|", 1) && ft_strlen(s->content) == 1)
	{
		return (true);
	}
	return (false);
}

// bool    is_valid_word(t_cmd *c, t_stack *s)
// {
//     s->token = ft_strdup("WORD");
//     return (true);
// }

int	identity_token(t_msh *msh)
{
	t_stack	*tmp;

	if (!msh || !msh->stack)
		return (0);
	tmp = msh->stack;
	while (tmp)
	{
		if (is_redir_symbol(tmp))
		{
			if (is_valid_redir(tmp))
				tmp->token = REDIR;
			else
			{
				g_exit_code = 2;
				ft_fprintf(2, "bash: syntax error near unexpected token `>>'");
			}
		}
		else if (is_valid_pipe(tmp))
			tmp->token = PIPE;
		else if (is_operation_symb(tmp))
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
		else
		{
			tmp->token = WORD;
			tmp->sub_token = NONE;
		}
		tmp = tmp->next;
	}
	tmp = msh->stack;
	while (tmp)
	{
		printf("%u %u\n", tmp->token, tmp->sub_token);
		tmp = tmp->next;
	}
	return (1);
}
