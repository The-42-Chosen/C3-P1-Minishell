/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:10:00 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/24 14:38:17 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_quotes(char *s, int *i, char quote_char)
{
	(*i)++;
	while (s[*i] != quote_char)
	{
		if (s[*i] == '\0')
		{
			if (quote_char == '\"')
				ft_fprintf(2, "Billyshell: unclosed dquotes\n");
			else
				ft_fprintf(2, "Billyshell: unclosed quotes\n");
			return (-1);
		}
		(*i)++;
	}
	(*i)++;
	return (0);
}

void	handle_word(char *s, int *i)
{
	while (s[*i] && !is_space(s[*i]))
	{
		(*i)++;
		if (is_delimeter(s[*i]))
			break ;
	}
}

char	*extract_word(t_msh *msh, char *s, int start, int end)
{
	int		len;
	char	*word;

	len = end - start;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	if (s[start] == '\"' || s[start] == '\'')
	{
		if (s[start] == '\'')
			msh->is_expandable = false;
		ft_memcpy(word, s + start + 1, len - 1);
		word[len - 2] = '\0';
	}
	else
	{
		ft_memcpy(word, s + start, len);
		word[len] = '\0';
	}
	return (word);
}
