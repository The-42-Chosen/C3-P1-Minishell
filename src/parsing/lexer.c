/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:02:15 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/24 14:38:17 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_entry(t_msh *msh, char *s, int *i)
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
		return (ft_fprintf(2, "Billyshell: syntax error `%c'\n", s[*i]), NULL);
	else if (s[*i] == '\"' || s[*i] == '\'')
	{
		if (handle_quotes(s, i, s[*i]) == -1)
			return (NULL);
	}
	else
		handle_word(s, i);
	if (*i == start)
		return (NULL);
	return (extract_word(msh, s, start, *i));
}

static int	process_word(t_msh *msh, char *word)
{
	char	*expanded;

	if (ft_strchr(word, '$') && msh->is_expandable == true)
	{
		expanded = expand(msh, word);
		free(word);
		word = expanded;
	}
	if (!word)
		return (0);
	add_word_to_stack(msh, word);
	free(word);
	return (1);
}

int	lexer(t_msh *msh)
{
	int		i;
	char	*word;

	if (!msh->entry)
		return (0);
	i = 0;
	while (msh->entry[i])
	{
		msh->is_expandable = true;
		word = read_entry(msh, msh->entry, &i);
		if (!word)
		{
			if (msh->entry[i] == '\0')
				break ;
			return (0);
		}
		if (!process_word(msh, word))
			return (0);
	}
	identify_token(msh);
	return (1);
}
