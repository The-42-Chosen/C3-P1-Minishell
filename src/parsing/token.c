/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:11:56 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/02 23:32:25 by gpollast         ###   ########.fr       */
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
		if (!classify_single_token(msh, tmp))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
