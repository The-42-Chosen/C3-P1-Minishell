/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 10:57:36 by erpascua          #+#    #+#             */
/*   Updated: 2025/09/22 11:07:23 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_received_signal = 0;

// void	free_msh(t_msh *msh)
// {

// }

// void	free_msh_builtins(t_msh *msh)
// {
// 	int	i;

// 	i = 0;
// 	while (i < NB_BUILTINS)
// 	{
// 		free(msh->builtin_names[i]);
// 		i++;
// 	}
// }

int	main(int ac, char **av, char **env)
{
	t_msh	msh;

	(void)ac;
	(void)av;
	if (!struct_init(&msh))
		return (msh.exit_code);
	save_env(&msh, env);
	print_banner();
	launch_program(&msh);
	data_destroy(msh.data);
	// free_msh_builtins(&msh);
	// free_msh(&msh);
	return (msh.exit_code);
}
