/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 10:57:36 by erpascua          #+#    #+#             */
/*   Updated: 2025/09/12 11:16:43 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;

int	env_dup(t_msh *msh, char **env)
{
	int	len;
	int	i;

	len = 0;
	while (env[len])
		len++;
	msh->env = malloc(sizeof(char *) * (len + 1));
	if (!msh->env)
	{
		g_exit_code = 2;
		return (0);
	}
	i = 0;
	while (env[i])
	{
		msh->env[i] = ft_strdup(env[i]);
		if (!msh->env[i])
		{
			g_exit_code = 2;			
			return (0);
		}
		i++;
	}
	msh->env[i] = NULL;
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_msh	msh;

	(void)ac;
	(void)av;
	print_banner();
	if (!struct_init(&msh))
		return (g_exit_code);
	if (!env_dup(&msh, env))
		return (g_exit_code);
	launch_program(&msh);
	// ft_free(&msh);
	return (g_exit_code);
}
