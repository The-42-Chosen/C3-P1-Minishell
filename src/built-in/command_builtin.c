/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:07:49 by erpascua          #+#    #+#             */
/*   Updated: 2025/09/22 13:29:05 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_builtin_type	get_builtin_type(t_msh *msh, t_data *data)
{
	int		i;
	char	**av;

	i = 1;
	av = data->cmd.args;
	if (!av || !av[0])
		return (BI_NONE);
	while (i < NB_BUILTINS)
	{
		if (!ft_strncmp(msh->builtin_names[i], av[0],
				ft_strlen(msh->builtin_names[i]) + 1))
			return (i);
		i++;
	}
	data->cmd.builtin_type = 0;
	return (BI_NONE);
}

bool	execute_builtin(t_msh *msh, t_data *data)
{
	char	**av;

	av = data->cmd.args;
	if (!av || !av[0])
		return (0);
	msh->builtin_funcs[data->cmd.builtin_type](msh, av);
	return (1);
}
