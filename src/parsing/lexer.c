/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:02:15 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/01 16:20:17 by gpollast         ###   ########.fr       */
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
		return (msh->exit_code = 2, ft_fprintf(2,
				"Billyshell: syntax error `%c'\n", s[*i]), NULL);
	else if (is_pipe(s[*i]) && is_pipe(s[*i + 1]))
		return (msh->exit_code = 2, ft_fprintf(2,
				"Billyshell: syntax error `%c%c'\n", s[*i], s[*i + 1]), NULL);
	else if (s[*i] == '(' || s[*i] == ')')
		return (msh->exit_code = 2, ft_fprintf(2,
				"Billyshell: syntax error `%c'\n", s[*i]), NULL);
	else if (s[*i] == '\"' || s[*i] == '\'')
	{
		if (handle_quotes(s, i, s[*i]) == -1)
			return (msh->exit_code = 2, NULL);
		if (s[*i] != 0 && !is_space(s[*i]))
			msh->is_append = true;
	}
	else
	{
		handle_word(s, i);
		if (s[*i] != 0 && !is_space(s[*i]))
			msh->is_append = true;
	}
	if (*i == start)
		return (NULL);
	return (extract_word(msh, s, start, *i));
}

static int	process_word(t_msh *msh, char *word, int flag)
{
	char	*expanded;
	int		ret;

	if (!word)
		return (0);
	if (ft_strchr(word, '$') && msh->is_expandable == true && !flag)
	{
		expanded = expand(msh, word);
		if (!expanded)
			return (0);
		ret = add_word_to_stack(msh, expanded);
		free(expanded);
		return (ret);
	}
	return (add_word_to_stack(msh, word));
}

int	lexer(t_msh *msh)
{
	int		i;
	char	*word;
	int		flag;

	if (!msh->entry)
		return (0);
	i = 0;
	flag = 0;
	word = NULL;
	while (msh->entry[i])
	{
		msh->is_append = false;
		msh->is_expandable = true;
		word = read_entry(msh, msh->entry, &i);
		if (!word)
			return (0);
		printf("|%s|\n", word);
		if (!process_word(msh, word, flag))
		{
			free(word);
			return (0);
		}
		if (!ft_strcmp(word, "<<"))
			flag = 1;
		free(word);
	}
	if (!word)
		printf("OK\n");
	if (!identify_token(msh))
		return (0);
	return (1);
}
