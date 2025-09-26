/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:10:00 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/26 11:37:58 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_delimeter(char c)
{
	if (c == '>' || c == '<' || c == '&' || c == '|')
		return (true);
	return (false);
}

bool	is_redirection(char c)
{
	if (c == '>' || c == '<')
		return (true);
	return (false);
}

bool	is_operator(char c)
{
	if (c == '&' || c == '|')
		return (true);
	return (false);
}

void	check_redirection(char *s, int *i)
{
	while (s[*i] && is_redirection(s[*i]))
		(*i)++;
}
