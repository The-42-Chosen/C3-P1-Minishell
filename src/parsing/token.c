/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:11:56 by gpollast          #+#    #+#             */
/*   Updated: 2025/08/29 13:18:18 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_redir(t_stack *s)
{
    if (!s || !s->content)
        return (false);
    if (!ft_strncmp(s->content, "<<", 2) && ft_strlen(s->content) == 2)
    {
        s->sub_token = ft_strdup("HEREDOC");
        return (true);
    }
    else if (!ft_strncmp(s->content, ">>", 2) && ft_strlen(s->content) == 2)
    {
        s->sub_token = ft_strdup("APPEND");
        return (true);
    }
    else if (!ft_strncmp(s->content, "<", 1) && ft_strlen(s->content) == 1)
    {
        s->sub_token = ft_strdup("IN");
        return (true);
    }
    else if (!ft_strncmp(s->content, ">", 1) && ft_strlen(s->content) == 1)
    {
        s->sub_token = ft_strdup("OUT");
        return (true);
    }
    return (false);
}

bool	is_valid_operator(t_stack *s)
{
    if (!s || !s->content)
        return (false);
    if (!ft_strncmp(s->content, "&&", 2) && ft_strlen(s->content) == 2)
    {
        s->sub_token = ft_strdup("AND");
        return (true);
    }
    else if (!ft_strncmp(s->content, "||", 2) && ft_strlen(s->content) == 2)
    {
        s->sub_token = ft_strdup("OR");
        return (true);
    }
    return (false);
}

bool	is_valid_pipe(t_stack *s)
{
    if (!s || !s->content)
        return (false);
    if (!ft_strncmp(s->content, "|", 1) && ft_strlen(s->content) == 1)
    {
        return (true);
    }
    return (false);
}

void	identity_token(t_msh *msh)
{
    t_stack	*tmp;

    if (!msh || !msh->stack)
        return;
    tmp = msh->stack;
    while (tmp)
    {
        if (is_valid_redir(tmp))
            tmp->token = ft_strdup("REDIR");
        else if (is_valid_pipe(tmp))
            tmp->token = ft_strdup("PIPE");
        else if (is_valid_operator(tmp))
            tmp->token = ft_strdup("OPERATOR");
        else
            tmp->token = ft_strdup("WORD");
        tmp = tmp->next;
    }
    tmp = msh->stack;
    while (tmp)
    {
        if (tmp->sub_token)
            printf("%s %s\n", tmp->token, tmp->sub_token);
        else
            printf("%s\n", tmp->token);
        tmp = tmp->next;
    }
}
