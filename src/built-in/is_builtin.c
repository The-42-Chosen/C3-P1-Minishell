/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:07:49 by erpascua          #+#    #+#             */
/*   Updated: 2025/08/22 11:55:09 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(t_msh *msh, char *s)
{
	int	i;
	int	i;

	i = 0;
	while (i < NB_BUILTINS)
	{
		if (!ft_strncmp(msh->builtin_names[i], s, ft_strlen(s) + 1))
		{
			msh->builtin_funcs[i]();
			msh->is_builtin = 1;
			return (1);
		}
		i++;
	}
	return (0);
}
