/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:02:15 by gpollast          #+#    #+#             */
/*   Updated: 2025/08/22 20:13:36 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_entry(char *s, int *i)
{
	int 	start;
	char 	*word;
	
	if (!s)
		return (NULL);
	while (is_space(s[*i]))
		(*i)++;
	start = *i;
	// ft_printf("start : %d\n", start);
	while (s[*i])
	{
		if (s[*i] == '\"' || s[*i] == '\'')
		{
			return (NULL);
		}
		if (s[*i + 1] == '\0' || is_space(s[*i + 1]))
		{
			word = malloc(sizeof(char) * (*i - start + 1));
			if (!word)
				return (NULL);
			// ft_printf("&s[start] : %s\n", &s[start]);
			ft_strlcpy(word, s + start, *i - start);
			return (word);
		}
		(*i)++;
	}
	return (NULL);
}

int	lexer(t_msh *msh)
{
	int 	i;
	char	*status;
	
	if (!msh->entry)
		return (0);
	i = 0;
	// ft_printf("%s\n", read_entry(&msh->entry[i]));
	// ft_printf("%s\n", &msh->entry[i]);
	msh->nodes = malloc(sizeof(t_node));
	while (1)
	{
		// ft_printf("entry : %s\n", &msh->entry[i]);
		status = read_entry(&msh->entry[i], &i);
		ft_printf("status : %s\n", status);
		if (!status)
			break ;
		ft_printf("%s\n", status);
		free(status);
		// msh->nodes->content = read_entry(&msh->entry[i], &i);
		// msh->nodes->content = msh->nodes->next->content;
	}
	return (0);
}
