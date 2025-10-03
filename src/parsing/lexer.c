/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:02:15 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/03 12:53:09 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	read_syntax_errors(t_msh *msh, char *s, int *i)
{
	if (is_operator(s[*i]))
		return (msh->exit_code = 2, ft_fprintf(2,
				"Billyshell: syntax error `%c'\n", s[*i]), 0);
	else if (is_pipe(s[*i]) && is_pipe(s[*i + 1]))
		return (msh->exit_code = 2, ft_fprintf(2,
				"Billyshell: syntax error `%c%c'\n", s[*i], s[*i + 1]), 0);
	else if (s[*i] == '(' || s[*i] == ')')
		return (msh->exit_code = 2, ft_fprintf(2,
				"Billyshell: syntax error `%c'\n", s[*i]), 0);
	return (1);
}

static int	read_entry_dispatch(t_msh *msh, char *s, int *i)
{
	if (is_redirection(s[*i]))
	{
		check_redirection(s, i);
		return (1);
	}
	if (is_pipe(s[*i]))
	{
		(*i)++;
		return (1);
	}
	if (!read_syntax_errors(msh, s, i))
		return (-1);
	if (s[*i] == '\"' || s[*i] == '\'')
	{
		if (read_quotes(msh, s, i) == -1)
			return (-1);
		return (1);
	}
	handle_word(s, i);
	if (s[*i] == '\"' || s[*i] == '\'')
		msh->is_append = true;
	return (1);
}

char	*read_entry(t_msh *msh, char *s, int *i)
{
	int	start;
	int	ret;

	if (!s)
		return (NULL);
	while (is_space(s[*i]))
		(*i)++;
	start = *i;
	ret = read_entry_dispatch(msh, s, i);
	if (ret < 0)
		return (NULL);
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
	if (msh->is_append == false && !ft_strncmp(word, "$", 2))
		return (add_word_to_stack(msh, word));
	else if (ft_strchr(word, '$') && msh->is_expandable == true && !flag)
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
		if (!process_word(msh, word, flag))
			return (free(word), 0);
		if (!ft_strcmp(word, "<<"))
			flag = 1;
		free(word);
	}
	if (!identify_token(msh))
		return (0);
	return (1);
}
