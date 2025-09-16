/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolved_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:46:48 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/16 17:08:17 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*my_getenv_for_path(t_msh *msh)
{
	int	i;

	i = 0;
	while (msh->env[i])
	{
		if (!ft_strncmp(msh->env[i], "PATH=", ft_strlen("PATH=")))
			return (msh->env[i]);
		i++;
	}
	return (NULL);
}

char	*path_env(char *str, char *cmd)
{
	char	**path_lst;
	char	*path;
	int		len;
	int		i;

	path_lst = ft_split(str, ":");
	if (!path_lst)
		return (NULL);
	i = -1;
	while (path_lst[++i])
	{
		len = ft_strlen(path_lst[i]) + ft_strlen(cmd) + 2;
		path = malloc(sizeof(char) * len);
		if (!path)
			return (free_tab(path_lst), NULL);
		ft_bzero(path, len);
		ft_strlcat(path, path_lst[i], len);
		ft_strlcat(path, "/", len);
		ft_strlcat(path, cmd, len);
		if (!access(path, X_OK))
			return (free_tab(path_lst), path);
		free(path);
	}
	return (free_tab(path_lst), NULL);
}

char	*cmd_path(t_msh *msh, char *cmd)
{
	char	**res;
	char	*path;

	res = ft_split(cmd, " \t");
	if (!res)
		return (NULL);
	if (cmd[0] == '/')
		path = ft_strdup(res[0]);
	else
		path = path_env(my_getenv_for_path(msh), res[0]);
	free_tab(res);
	if (!path)
		return (NULL);
	return (path);
}
