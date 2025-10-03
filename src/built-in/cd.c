/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:28:44 by ubuntu            #+#    #+#             */
/*   Updated: 2025/10/03 11:07:05 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_error(t_msh *msh, t_process *process)
{
	(void)msh;
	ft_fprintf(2,
		"Billyshell: chdir: error retrieving current directory: "
		"getcwd: cannot access parent directories: %s\n",
		strerror(errno));
	process->bi_exit_code = 1;
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
		if (ft_strncmp(tmp->key, "PWD", 4) == 0 && tmp->key[3] == '\0')
			paths->pwd = ft_strdup(tmp->value);
		if (ft_strncmp(tmp->key, "OLDPWD", 7) == 0 && tmp->key[6] == '\0')
		{
			paths->oldpwd = ft_strdup(tmp->value);
			paths->has_oldpwd = true;
		}
		if (ft_strncmp(tmp->key, "HOME", 5) == 0 && tmp->key[4] == '\0')
		{
			paths->home = ft_strdup(tmp->value);
			paths->has_home = true;
		}
		tmp = tmp->next;
	}
}

void	cd_update_env(t_env *env, t_process *process, t_paths *paths)
{
	t_env	*tmp;
	char	*old_pwd_value;

	(void)process;
	old_pwd_value = NULL;
	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "PWD", 4) == 0 && tmp->key[3] == '\0')
		{
			old_pwd_value = ft_strdup(tmp->value);
			free(tmp->value);
			tmp->value = ft_strdup(paths->pwd);
		}
		tmp = tmp->next;
	}
	tmp = env;
	while (tmp && ft_strncmp(tmp->key, "OLDPWD", 7) != 0)
		tmp = tmp->next;
	if (tmp && tmp->key[6] == '\0')
	{
		free(tmp->value);
		tmp->value = ft_strdup(old_pwd_value);
	}
	free(old_pwd_value);
}

void	cd_dispatcher(t_msh *msh, t_process *process, char **av, int i)
{
	if (i == 1 || (ft_strncmp(av[1], "~", 1) == 0 && av[1][1] == '\0'))
	{
		if (cd_home(process, msh->env, &msh->paths))
			process->bi_exit_code = 0;
	}
	else if (ft_strncmp(av[1], "-", 1) == 0 && av[1][1] == '\0')
	{
		if (cd_oldpwd(msh, process, msh->env, &msh->paths))
			process->bi_exit_code = 0;
	}
	else
	{
		if (cd_folder(msh, process, &msh->paths, av[1]))
			process->bi_exit_code = 0;
	}
}

int	bi_cd(t_msh *msh, t_process *process, char **av)
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
		process->bi_exit_code = 1;
		return (1);
	}
	cd_get_paths(msh->env, &msh->paths);
	cd_dispatcher(msh, process, av, i);
	free(msh->paths.home);
	free(msh->paths.pwd);
	free(msh->paths.oldpwd);
	return (0);
}
