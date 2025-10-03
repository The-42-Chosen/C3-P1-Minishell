/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_folder.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 20:56:41 by ubuntu            #+#    #+#             */
/*   Updated: 2025/10/03 14:35:44 by gpollast         ###   ########.fr       */
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

static char	*cd_absolute_path(t_process *process, t_paths *paths, char *folder)
{
	char	*target_path;
	char	*cwd;

	if (folder[0] == '/')
	{
		target_path = ft_strdup(folder);
		if (!target_path)
			return (process->bi_exit_code = 12, NULL);
	}
	else
	{
		target_path = unify_path(paths, folder);
		if (!target_path)
		{
			cwd = getcwd(NULL, 0);
			if (!cwd)
			{
				ft_fprintf(2,
					"Billyshell: chdir: error retrieving current "
					"directory: getcwd: cannot access parent directories: "
					"%s\n", strerror(errno));
				return (process->bi_exit_code = 1, NULL);
			}
			free(cwd);
			return (process->bi_exit_code = 1, ft_fprintf(2, "Billyshell: cd: "
					"error retrieving current directory\n"), NULL);
		}
	}
	return (target_path);
}

static bool	cd_change_dir(t_msh *msh, t_process *process, t_paths *paths,
	char *path)
{
	char	*real_path;
	char	*cwd;

	real_path = getcwd(NULL, 0);
	if (real_path)
	{
		free(paths->pwd);
		paths->pwd = ft_strdup(real_path);
		if (!paths->pwd)
			return (process->bi_exit_code = 12, false);
		free(real_path);
	}
	else
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
			return (cd_error(msh, process), free(path), false);
		free(cwd);
		return (ft_fprintf(2,
				"Billyshell: cd: error retrieving current directory\n"),
			process->bi_exit_code = 1, false);
	}
	free(path);
	if (!cd_update_env(msh->env, process, paths))
		return (false);
	return (true);
}

static bool	cd_check_folder(t_process *process, char *target_path)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_fprintf(2,
			"Billyshell: chdir: error retrieving current directory: "
			"getcwd: cannot access parent directories: %s\n",
			strerror(errno));
		process->bi_exit_code = 1;
		free(target_path);
		return (false);
	}
	free(cwd);
	return (ft_fprintf(2, "Billyshell: cd: %s: No such file or directory\n",
			target_path), free(target_path), process->bi_exit_code = 1, false);
}

bool	cd_folder(t_msh *msh, t_process *process, t_paths *paths,
		char *folder)
{
	char	*target_path;

	target_path = cd_absolute_path(process, paths, folder);
	if (chdir(target_path) == 0)
		return (cd_change_dir(msh, process, paths, target_path));
	else
		return (cd_check_folder(process, target_path));
	return (true);
}
