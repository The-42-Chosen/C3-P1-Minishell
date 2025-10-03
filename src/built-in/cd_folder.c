/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_folder.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 20:56:41 by ubuntu            #+#    #+#             */
/*   Updated: 2025/10/03 16:53:17 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_null_target_path(t_process *process)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_fprintf(2,
			"Billyshell: chdir: error retrieving current "
			"directory: getcwd: cannot access parent directories: "
			"%s\n",
			strerror(errno));
		return (process->bi_exit_code = 1, 0);
	}
	free(cwd);
	return (process->bi_exit_code = 1, ft_fprintf(2,
			"Billyshell: cd: "
			"error retrieving current directory\n"),
		0);
	return (1);
}

static char	*cd_absolute_path(t_process *process, t_paths *paths, char *folder)
{
	char	*target_path;

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
			if (!cd_null_target_path(process))
				return (NULL);
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
	if (!cd_update_env(msh->env, process, paths))
		return (free(path), false);
	return (free(path), true);
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

bool	cd_folder(t_msh *msh, t_process *process, t_paths *paths, char *folder)
{
	char	*target_path;

	target_path = cd_absolute_path(process, paths, folder);
	if (chdir(target_path) == 0)
		return (cd_change_dir(msh, process, paths, target_path));
	else
		return (cd_check_folder(process, target_path));
	return (true);
}
