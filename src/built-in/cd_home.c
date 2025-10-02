/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_home.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 20:43:25 by ubuntu            #+#    #+#             */
/*   Updated: 2025/10/02 14:39:26 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	cd_home_success(t_env *env, t_process *process, t_paths *paths)
{
	char	*real_path;

	real_path = getcwd(NULL, 0);
	if (real_path)
	{
		free(paths->pwd);
		paths->pwd = ft_strdup(real_path);
		free(real_path);
	}
	else
	{
		free(paths->pwd);
		paths->pwd = ft_strdup(paths->home);
	}
	cd_update_env(env, process, paths);
	return (true);
}

static bool	cd_home_error(t_process *process, t_paths *paths)
{
	ft_fprintf(2, "Billyshell: cd: %s: No such file or directory\n",
		paths->home);
	process->bi_exit_code = 1;
	return (false);
}

bool	cd_home(t_process *process, t_env *env, t_paths *paths)
{
	if (paths->has_home)
	{
		if (chdir(paths->home) == 0)
			return (cd_home_success(env, process, paths));
		else
			return (cd_home_error(process, paths));
	}
	else
	{
		ft_fprintf(2, "Billyshell: cd: HOME not set\n");
		process->bi_exit_code = 1;
		return (false);
	}
}
