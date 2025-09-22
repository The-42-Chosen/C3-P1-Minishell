/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:00:00 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/22 11:07:23 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*seek_group_redir(t_msh *msh, t_stack *stack)
{
	char	*res;

	if (stack->token == REDIR && stack->next
		&& stack->next->token == WORD)
	{
		res = ft_strdup(stack->next->content);
		if (!res)
		{
			msh->exit_code = 12;
			return (NULL);
		}
		stack = stack->next;
		return (res);
	}
	msh->exit_code = 2;
	if (!stack->next)
		ft_fprintf(2, "bash: syntax error near unexpected token `newline'\n");
	else if (stack->next->token != WORD)
		ft_fprintf(2, "bash: syntax error near unexpected token `%s'\n",
			stack->next->content);
	return (NULL);
}

static t_group	identify_redir(char *word)
{
	int	len;

	len = ft_strlen(word);
	if (!ft_strncmp(word, "<", len))
		return (G_REDIR_IN);
	else if (!ft_strncmp(word, ">", len))
		return (G_REDIR_OUT);
	else if (!ft_strncmp(word, "<<", len))
		return (G_REDIR_HEREDOC);
	else if (!ft_strncmp(word, ">>", len))
		return (G_REDIR_APPEND);
	return (G_INVALID);
}

int	add_redir_node(t_msh *msh, t_stack **tmp, t_data *new_node)
{
	new_node->file_or_limiter = seek_group_redir(msh, *tmp);
	if (!new_node->file_or_limiter)
		return (0);
	new_node->group = identify_redir((*tmp)->content);
	(*tmp) = (*tmp)->next;
	return (1);
}
