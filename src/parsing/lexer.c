/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:02:15 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/10 18:42:23 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_entry(char *s, int *i)
{
	int	start;

	if (!s)
		return (NULL);
	while (is_space(s[*i]))
		(*i)++;
	start = *i;
	if (is_redirection(s[*i]))
		check_redirection(s, i);
	else if (is_operator(s[*i]))
		check_operator(s, i);
	else if (s[*i] == '(' || s[*i] == ')')
		return (ft_fprintf(2, "bash: syntax error `%c'\n", s[*i]), NULL);
	else if (s[*i] == '\"' || s[*i] == '\'')
	{
		if (handle_quotes(s, i, s[*i]) == -1)
			return (NULL);
	}
	else
		handle_word(s, i);
	if (*i == start)
		return (NULL);
	return (extract_word(s, start, *i));
}

int	lexer(t_msh *msh)
{
	int		i;
	char	*word;

	if (!msh->entry)
		return (0);
	i = 0;
	while (1)
	{
		word = read_entry(msh->entry, &i);
		if (!word)
			break ;
		add_word_to_stack(msh, word);
		free(word);
	}
	identity_token(msh);
	return (1);
}
