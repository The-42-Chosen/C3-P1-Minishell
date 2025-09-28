/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:28:44 by ubuntu            #+#    #+#             */
/*   Updated: 2025/09/28 23:29:08 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_error(t_msh *msh)
{
	ft_fprintf(2, "Billyshell: chdir: error retrieving current directory: "
		"getcwd: cannot access parent directories: %s\n", strerror(errno));
	msh->exit_code = 1;
}

void	cd_get_paths(t_env *env, t_paths *paths)
{
	t_env	*tmp;

	tmp = env;
	paths->has_home = false;
	paths->has_oldpwd = false;
	paths->pwd = NULL;
	paths->oldpwd = NULL;
	paths->home = NULL;
	while (tmp)
	{
		if (strncmp(tmp->key, "PWD", 4) == 0 && tmp->key[3] == '\0')
			paths->pwd = ft_strdup(tmp->value);
		if (strncmp(tmp->key, "OLDPWD", 7) == 0 && tmp->key[6] == '\0')
		{
			paths->oldpwd = ft_strdup(tmp->value);
			paths->has_oldpwd = true;
		}
		if (strncmp(tmp->key, "HOME", 5) == 0 && tmp->key[4] == '\0')
		{
			paths->home = ft_strdup(tmp->value);
			paths->has_home = true;
		}
		tmp = tmp->next;
	}
}

void	cd_update_env(t_env *env, t_paths *paths)
{
	t_env	*tmp;
	char	*old_pwd_value;

	old_pwd_value = NULL;
	tmp = env;
	while (tmp)
	{
		if (strncmp(tmp->key, "PWD", 4) == 0 && tmp->key[3] == '\0')
		{
			old_pwd_value = ft_strdup(tmp->value);
			free(tmp->value);
			tmp->value = ft_strdup(paths->pwd);
		}
		tmp = tmp->next;
	}
	tmp = env;
	while (tmp && strncmp(tmp->key, "OLDPWD", 7) != 0)
		tmp = tmp->next;
	if (tmp && tmp->key[6] == '\0')
	{
		free(tmp->value);
		tmp->value = ft_strdup(old_pwd_value);
	}
	free(old_pwd_value);
}

int	bi_cd(t_msh *msh, char **av)
{
	int	i;

	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		return (0);
	i = 1;
	while (av[i])
		i++;
	if (i > 2)
	{
		ft_fprintf(2, "Billyshell: cd: too many arguments\n");
		msh->exit_code = 1;
		return (1);
	}
	cd_get_paths(msh->env, &msh->paths);
	if (i == 1 || (ft_strncmp(av[1], "~", 1) == 0 && av[1][1] == '\0'))
		cd_home(msh, msh->env, &msh->paths);
	else if (ft_strncmp(av[1], "-", 1) == 0 && av[1][1] == '\0')
		cd_oldpwd(msh, msh->env, &msh->paths);
	else
		cd_folder(msh, msh->env, &msh->paths, av[1]);
	free(msh->paths.home);
	free(msh->paths.pwd);
	free(msh->paths.oldpwd);
	return (0);
}
