/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:02:15 by gpollast          #+#    #+#             */
/*   Updated: 2025/08/25 17:24:40 by gpollast         ###   ########.fr       */
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

char	*read_entry(char *s, int *i)
{
    int 	start;
    char 	*word;
    int		len;
    
    if (!s)
        return (NULL);
    while (is_space(s[*i]))
        (*i)++;
    start = *i;
	if (is_redirection(s[*i]))
		check_redirection(s, i);
	else if (is_operator(s[*i]))
		check_operator(s, i);
	else if (s[*i] == '\"')
	{
		(*i)++;
		while (s[*i] != '\"')
			(*i)++;
		(*i)++;
	}
	else if (s[*i] == '\'')
	{
		(*i)++;
		while (s[*i] != '\'')
			(*i)++;
		(*i)++;
	}
	else
    	while (s[*i] && !is_space(s[*i]))
		{
    	    (*i)++;
			if (is_delimeter(s[*i]))
				break ;
		}
    if (*i == start)
	{
    	return (NULL);
	}
    len = *i - start;
    word = malloc(sizeof(char) * (len + 1));
    if (!word)
        return (NULL);
    ft_memcpy(word, s + start, len);
    word[len] = '\0';
    return (word);
}

int	lexer(t_msh *msh)
{
	int 	i;
	char	*word;
	int		tour;
	
	tour = 0;
	if (!msh->entry)
		return (0);
	i = 0;
	while (1)
	{
		// ft_printf("Tour[%d]\n", tour);
		tour++;
		word = read_entry(msh->entry, &i);
		ft_printf("%s\n", word);
		if (!word)
			break ;
		free(word);
	}
	return (0);
}
