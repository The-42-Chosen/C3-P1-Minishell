/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:11:56 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/22 11:07:23 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	print_tokens_debug(t_stack *stack)
// {
// 	t_stack	*tmp;

// 	tmp = stack;
// 	while (tmp)
// 	{
// 		printf("%u %u\n", tmp->token, tmp->sub_token);
// 		tmp = tmp->next;
// 	}
// }

int	identify_token(t_msh *msh)
{
	t_stack	*tmp;

	if (!msh || !msh->stack)
		return (0);
	tmp = msh->stack;
	while (tmp)
	{
		classify_single_token(msh, tmp);
		tmp = tmp->next;
	}
	return (1);
}
