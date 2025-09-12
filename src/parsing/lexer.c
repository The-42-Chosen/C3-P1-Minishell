/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:02:15 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/12 16:17:08 by gpollast         ###   ########.fr       */
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
	return (extract_word(msh, s, start, *i));
}

char	*find_expand_symbol(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '$')
			return (word + i);
		i++;
	}
	return (NULL);
}

char	*my_getenv(t_msh *msh, char *word)
{
	int	i;
	
	i = 0;
	while (msh->env[i])
	{
		if (!ft_strncmp(msh->env[i], word + 1, ft_strlen(word + 1)))
			return (msh->env[i]);
		i++;
	}
	return (NULL);
}

char	*expand(t_msh *msh, char *word)
{
	char	*res;
	char	*env_str;
	
	res = NULL;
	env_str = my_getenv(msh, word);
	if (env_str)
		res = ft_strdup(env_str + ft_strlen(word));
	else
		res = ft_strdup("");
	if (!res)
		return (NULL);
	free(word);
	return (res);
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
		msh->is_expandable = true;
		word = read_entry(msh, msh->entry, &i);
		if (!word)
			break ;
		if (find_expand_symbol(word) && msh->is_expandable == true)
			word = expand(msh, word);
		if (!word)
			return (0);
		add_word_to_stack(msh, word);
		free(word);
	}
	identify_token(msh);
	return (1);
}
