/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 19:02:46 by erpascua          #+#    #+#             */
/*   Updated: 2025/10/03 14:30:52 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_pwd_env(t_msh *msh, char *new_pwd)
{
	t_env	*tmp;

	tmp = msh->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "PWD", 4) == 0 && tmp->key[3] == '\0')
		{
			free(tmp->value);
			tmp->value = ft_strdup(new_pwd);
			if (!tmp->value)
				return (0);
			return (1);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	bi_pwd(t_msh *msh, t_process *process, char **av)
{
	char	*cwd;

	(void)av;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_fprintf(2, "Billyshell: pwd: error retrieving current directory: ");
		ft_fprintf(2, "getcwd: cannot access parent directories: ");
		ft_fprintf(2, "No such file or directory\n");
		process->bi_exit_code = 1;
		return (1);
	}
	if (!update_pwd_env(msh, cwd))
		return (msh->exit_code = 2, 1);
	ft_fprintf(1, "%s\n", cwd);
	free(cwd);
	process->bi_exit_code = 0;
	return (0);
}
