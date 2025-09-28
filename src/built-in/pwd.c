/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 19:02:46 by erpascua          #+#    #+#             */
/*   Updated: 2025/09/28 20:27:42 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd_env(t_msh *msh, char *new_pwd)
{
	t_env	*tmp;

	tmp = msh->env;
	while (tmp)
	{
		if (strncmp(tmp->key, "PWD", 4) == 0 && tmp->key[3] == '\0')
		{
			free(tmp->value);
			tmp->value = ft_strdup(new_pwd);
			return ;
		}
		tmp = tmp->next;
	}
}

int	bi_pwd(t_msh *msh, char **av)
{
	char	*cwd;

	(void)av;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_fprintf(2,
			"Billyshell: pwd: error retrieving current directory: getcwd: cannot access parent directories: %s\n",
			strerror(errno));
		return (1);
	}
	update_pwd_env(msh, cwd);
	ft_fprintf(1, "%s\n", cwd);
	free(cwd);
	return (0);
}
