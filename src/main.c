/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ep <ep@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 10:57:36 by erpascua          #+#    #+#             */
/*   Updated: 2025/09/17 03:47:34 by ep               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;

int	main(int ac, char **av, char **env)
{
	t_msh	msh;

	(void)ac;
	(void)av;
	struct_init(&msh);
	save_env(&msh, env);
	print_banner();
	launch_program(&msh);
	return (g_exit_code);
}
