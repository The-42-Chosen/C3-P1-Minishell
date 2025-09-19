/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ep <ep@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 10:57:36 by erpascua          #+#    #+#             */
/*   Updated: 2025/09/19 17:02:22 by ep               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exit_code = 0;

int	env_dup(t_msh *msh, char **env)
{
	int	len;
	int	i;

	len = 0;
	while (env[len])
		len++;
	msh->env = malloc(sizeof(char *) * (len + 1));
	if (!msh->env)
		return (g_exit_code = 2, 0);
	i = 0;
	while (env[i])
	{
		msh->env[i] = ft_strdup(env[i]);
		if (!msh->env[i])
		{
			while (--i >= 0)
				free(msh->env[i]);
			free(msh->env);
			msh->env = NULL;
			return (g_exit_code = 2, 0);
		}
		i++;
	}
	msh->env[i] = NULL;
	return (1);
}

// void	free_msh(t_msh *msh)
// {

// }

void	free_msh_builtins(t_msh *msh)
{
	int	i;

	i = 0;
	while (i < NB_BUILTINS)
	{
		free(msh->builtin_names[i]);
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	t_msh	msh;

	(void)ac;
	(void)av;
	if (!struct_init(&msh))
		return (g_exit_code);
	save_env(&msh, env);
	print_banner();
	launch_program(&msh);
	data_destroy(msh.data);
	if (msh.env)
		free_tab(msh.env);
	free_msh_builtins(&msh);
	// free_msh(&msh);
	return (g_exit_code);
}
