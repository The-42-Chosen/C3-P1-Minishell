/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ep <ep@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:07:49 by erpascua          #+#    #+#             */
/*   Updated: 2025/09/16 09:32:11 by ep               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(t_msh *msh)
{
	int		i;
	char	**argv;

	i = 0;
	argv = split_spaces(msh->entry);
	if (!argv || !argv[0])
		return (0);
	while (i < NB_BUILTINS)
	{
		if (!ft_strncmp(msh->builtin_names[i], argv[0],
				ft_strlen(msh->builtin_names[i]) + 1))
		{
			msh->builtin_funcs[i](argv);
			free_tab(argv);
			msh->is_builtin = 1;
			return (1);
		}
		i++;
	}
	free_tab(argv);
	msh->is_builtin = 0;
	return (0);
}
