/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:11:56 by gpollast          #+#    #+#             */
/*   Updated: 2025/08/25 20:12:00 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool    is_valid_redir(t_stack **s)
{
    if (!ft_strncmp((*s)->content, "<", ft_strlen((*s)->content)))
    {
        ft_printf("< OK\n");
        return (true);    
    }
    else if (!ft_strncmp((*s)->content, ">", ft_strlen((*s)->content)))
    {
        ft_printf("> OK\n");
        return (true);    
    }
    else if (!ft_strncmp((*s)->content, "<<", ft_strlen((*s)->content)))
    {
        ft_printf("<< OK\n");
        return (true);    
    }
    else if (!ft_strncmp((*s)->content, ">>", ft_strlen((*s)->content)))
    {
        ft_printf(">> OK\n");
        return (true);    
    }
    return (false);
}

void    identity_token(t_msh *msh)
{
    t_stack *tmp;

    tmp = msh->stack;
    while (tmp)
    {
        if (is_valid_redir(&tmp))
            ft_printf("OP\n", tmp->content);
        // else if (is_valid_operator(&tmp))
        //     ft_printf("NOP\n", tmp->content);
        tmp = tmp->next;
    }
}