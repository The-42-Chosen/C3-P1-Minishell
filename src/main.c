/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 10:57:36 by erpascua          #+#    #+#             */
/*   Updated: 2025/10/02 15:26:53 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_received_signal = 0;

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
	free_msh_builtins(&msh);
	free_msh(&msh);
	return (msh.exit_code);
}
