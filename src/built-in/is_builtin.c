/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ep <ep@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:07:49 by erpascua          #+#    #+#             */
/*   Updated: 2025/09/17 02:27:05 by ep               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(t_msh *msh)
{
	int		i;
	char	**av;

	i = 0;
	av = split_spaces(msh->entry);
	if (!av || !av[0])
		return (0);
	while (i < NB_BUILTINS)
	{
		if (!ft_strncmp(msh->builtin_names[i], av[0],
				ft_strlen(msh->builtin_names[i]) + 1))
		{
			msh->builtin_funcs[i](msh, av);
			free_tab(av);
			msh->is_builtin = 1;
			return (1);
		}
		i++;
	}
	free_tab(av);
	msh->is_builtin = 0;
	return (0);
}
