/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_paths.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:32:53 by erpascua          #+#    #+#             */
/*   Updated: 2025/10/03 16:26:26 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_init_paths(t_paths *paths)
{
	paths->has_home = false;
	paths->has_oldpwd = false;
	paths->pwd = NULL;
	paths->oldpwd = NULL;
	paths->home = NULL;
}

static int	cd_seek_pwd(t_env *env, t_paths *paths)
{
	paths->pwd = ft_strdup(env->value);
	if (!paths->pwd)
		return (0);
	return (1);
}

static int	cd_seek_oldpwd(t_env *env, t_paths *paths)
{
	paths->oldpwd = ft_strdup(env->value);
	if (!paths->oldpwd)
		return (0);
	paths->has_oldpwd = true;
	return (1);
}

static int	cd_seek_home(t_env *env, t_paths *paths)
{
	paths->home = ft_strdup(env->value);
	if (!paths->home)
		return (0);
	paths->has_home = true;
	return (1);
}

int	cd_get_paths(t_env *env, t_paths *paths)
{
	t_env	*tmp;

	tmp = env;
	cd_init_paths(paths);
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "PWD", 4) == 0 && tmp->key[3] == '\0')
		{
			if (!cd_seek_pwd(tmp, paths))
				return (0);
		}
		if (ft_strncmp(tmp->key, "OLDPWD", 7) == 0 && tmp->key[6] == '\0')
		{
			if (!cd_seek_oldpwd(tmp, paths))
				return (0);
		}
		if (ft_strncmp(tmp->key, "HOME", 5) == 0 && tmp->key[4] == '\0')
		{
			if (!cd_seek_home(tmp, paths))
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
