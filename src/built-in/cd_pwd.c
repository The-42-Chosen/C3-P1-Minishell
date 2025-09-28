/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ep <ep@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 20:46:52 by ubuntu            #+#    #+#             */
/*   Updated: 2025/09/28 23:37:25 by ep               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	cd_oldpwd_success(t_env *env, t_paths *paths)
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
		paths->pwd = ft_strdup(paths->oldpwd);
	}
	cd_update_env(env, paths);
	return (true);
}

static bool	cd_oldpwd_error(t_msh *msh, t_paths *paths)
{
	ft_fprintf(2, "Billyshell: cd: %s: No such file or directory\n",
		paths->oldpwd);
	msh->exit_code = 1;
	return (false);
}

bool	cd_oldpwd(t_msh *msh, t_env *env, t_paths *paths)
{
	if (paths->has_oldpwd && paths->oldpwd)
	{
		if (chdir(paths->oldpwd) == 0)
			return (cd_oldpwd_success(env, paths));
		else
			return (cd_oldpwd_error(msh, paths));
	}
	else
	{
		ft_fprintf(2, "Billyshell: cd: OLDPWD not set\n");
		msh->exit_code = 1;
		return (false);
	}
	return (true);
}
