/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:35:00 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/01 17:54:31 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_heredoc_append(t_stack *s)
{
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
	return (false);
}

bool	check_in_out(t_stack *s)
{
	if (!ft_strncmp(s->content, "<", 1) && ft_strlen(s->content) == 1)
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

bool	is_valid_redir(t_stack *s)
{
	if (!s || !s->content)
		return (false);
	if (check_heredoc_append(s))
		return (true);
	if (check_in_out(s))
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
