/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_folder.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ep <ep@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 20:56:41 by ubuntu            #+#    #+#             */
/*   Updated: 2025/09/29 00:33:45 by ep               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	*cd_absolute_path(t_msh *msh, t_paths *paths, char *folder)
{
	char	*target_path;
	char	*cwd;

	if (folder[0] == '/')
		target_path = ft_strdup(folder);
	else
	{
		target_path = unify_path(paths, folder);
		if (!target_path)
		{
			cwd = getcwd(NULL, 0);
			if (!cwd)
			{
				cd_error(msh, target_path);
				return (NULL);
			}
			free(cwd);
			return (ft_fprintf(2,
					"Billyshell: cd: error retrieving current directory\n"),
				msh->exit_code = 1, NULL);
		}
	}
	return (target_path);
}

static bool	cd_change_dir(t_msh *msh, t_env *env, t_paths *paths, char *path)
{
	char	*real_path;
	char	*cwd;

	real_path = getcwd(NULL, 0);
	if (real_path)
	{
		free(paths->pwd);
		paths->pwd = ft_strdup(real_path);
		free(real_path);
	}
	else
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
			return (free(path), cd_error(msh, path), false);
		free(cwd);
		return (ft_fprintf(2,
				"Billyshell: cd: error retrieving current directory\n"),
			msh->exit_code = 1, false);
	}
	free(path);
	cd_update_env(env, paths);
	return (true);
}

static bool	cd_check_folder(t_msh *msh, char *target_path)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		free(target_path);
		{
			cd_error(msh, target_path);
			free(target_path);
			msh->exit_code = 1;
			return (false);
		}
	}
	free(cwd);
	return (ft_fprintf(2, "Billyshell: cd: %s: No such file or directory\n",
			target_path), free(target_path), msh->exit_code = 1, false);
}

bool	cd_folder(t_msh *msh, t_env *env, t_paths *paths, char *folder)
{
	char	*target_path;

	target_path = cd_absolute_path(msh, paths, folder);
	if (chdir(target_path) == 0)
		return (cd_change_dir(msh, env, paths, target_path));
	else
		return (cd_check_folder(msh, target_path));
	return (true);
}
