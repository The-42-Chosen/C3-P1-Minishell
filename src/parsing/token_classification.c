/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_classification.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:35:00 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/02 23:32:55 by gpollast         ###   ########.fr       */
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
	if (s->content && (!ft_strncmp(s->content, "||", ft_strlen(s->content))
			|| ft_strncmp(s->content, "&&", ft_strlen(s->content))))
		return (true);
	return (false);
}

int	handle_redirection_token(t_msh *msh, t_stack *tmp)
{
	if (is_valid_redir(tmp))
		tmp->token = REDIR;
	else
	{
		msh->exit_code = 2;
		if (ft_strlen(tmp->content) == 3)
			ft_fprintf(2,
				"Billyshell: syntax error near unexpected token `%c'\n",
				tmp->content[2]);
		else
			ft_fprintf(2,
				"Billyshell: syntax error near unexpected token `%c%c'\n",
				tmp->content[2], tmp->content[3]);
		return (0);
	}
	return (1);
}

int	classify_single_token(t_msh *msh, t_stack *tmp)
{
	if (is_redir_symbol(tmp))
	{
		if (!handle_redirection_token(msh, tmp))
			return (0);
	}
	else if (is_valid_pipe(tmp))
		tmp->token = PIPE;
	else
		tmp->token = WORD;
	return (1);
}
