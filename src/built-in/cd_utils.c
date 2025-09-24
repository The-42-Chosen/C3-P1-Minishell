/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 06:45:30 by ep                #+#    #+#             */
/*   Updated: 2025/09/24 14:40:35 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	cd_home(t_msh *msh, t_env *env, t_paths *paths)
{
	if (paths->has_home)
	{
		free(paths->pwd);
		paths->pwd = ft_strdup(paths->home);
		cd_update_env(env, paths);
		chdir(paths->pwd);
	}
	else
	{
		ft_fprintf(1, "Billyshell: cd: HOME not set\n");
		msh->exit_code = 1;
		return (false);
	}
	return (true);
}

bool	cd_oldpwd(t_msh *msh, t_env *env, t_paths *paths)
{
	if (paths->has_oldpwd && paths->oldpwd)
	{
		free(paths->pwd);
		paths->pwd = ft_strdup(paths->oldpwd);
		ft_fprintf(1, "%s\n", paths->pwd);
		cd_update_env(env, paths);
		chdir(paths->pwd);
	}
	else
	{
		ft_fprintf(2, "Billyshell: cd: OLDPWD not set\n");
		msh->exit_code = 1;
		return (false);
	}
	return (true);
}

static char	*unify_path(t_paths *paths, char *folder)
{
	char	*slash_folder;
	char	*target_path;
	char	*current_dir;

	if (!paths->pwd)
	{
		current_dir = getcwd(NULL, 0);
		if (!current_dir)
			return (NULL);
	}
	else
		current_dir = paths->pwd;
	slash_folder = ft_strjoin("/", folder);
	target_path = ft_strjoin(current_dir, slash_folder);
	free(slash_folder);
	if (!paths->pwd)
		free(current_dir);
	return (target_path);
}

bool	cd_folder(t_msh *msh, t_env *env, t_paths *paths, char *folder)
{
	char	*target_path;

	if (folder[0] == '/')
		target_path = ft_strdup(folder);
	else
	{
		target_path = unify_path(paths, folder);
		if (!target_path)
			return (ft_fprintf(2, "cd: error retrieving current directory\n"),
				msh->exit_code = 1, false);
	}
	if (chdir(target_path) == 0)
	{
		free(paths->pwd);
		paths->pwd = ft_strdup(target_path);
		free(target_path);
		cd_update_env(env, paths);
		return (true);
	}
	else
		return (ft_fprintf(2, "Billyshell: cd: %s: No such file or directory\n",
				folder), free(target_path), msh->exit_code = 1, false);
}
