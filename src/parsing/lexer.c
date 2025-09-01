/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:02:15 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/01 15:26:59 by gpollast         ###   ########.fr       */
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
	int		start;
	char	*word;
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
		{
			if (s[*i] == '\0')
			{
				ft_fprintf(2, "bash: unclosed dquotes\n");
				return (NULL);
			}
			(*i)++;
		}
		(*i)++;
	}
	else if (s[*i] == '\'')
	{
		(*i)++;
		while (s[*i] != '\'')
		{
			if (s[*i] == '\0')
			{
				ft_fprintf(2, "bash: unclosed quotes\n");
				return (NULL);
			}
			(*i)++;
		}
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

void	print_stack(t_stack *s)
{
	t_stack	*tmp;

	tmp = s;
	while (tmp)
	{
		ft_fprintf(1, "%s\n", tmp->content);
		tmp = tmp->next;
	}
}

int	lexer(t_msh *msh)
{
	int		i;
	char	*word;
	t_stack	*tmp;

	if (!msh->entry)
		return (0);
	i = 0;
	while (1)
	{
		word = read_entry(msh->entry, &i);
		if (!word)
			break ;
		if (!msh->stack)
			msh->stack = new_stack(word);
		else
		{
			tmp = new_stack(word);
			stack_add_back(&msh->stack, tmp);
		}
		free(word);
	}
	// print_stack(msh->stack);
	identity_token(msh);
	parse(msh);
	stack_destroy(msh->stack);
	msh->stack = NULL;
	return (1);
}
