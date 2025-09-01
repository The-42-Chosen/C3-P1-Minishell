/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:10:00 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/01 16:14:29 by gpollast         ###   ########.fr       */
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

void	check_operator(char *s, int *i)
{
	while (s[*i] && is_operator(s[*i]))
		(*i)++;
}
