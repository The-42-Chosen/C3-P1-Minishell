/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolved_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:46:48 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/22 14:37:30 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*my_getenv_for_path(t_msh *msh)
{
	t_env	*env;

	env = msh->env;
	while (env)
	{
		if (!ft_strncmp(env->key, "PATH", ft_strlen("PATH")))
			return (env->value);
		env = env->next;
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
	char	*path;

	if (ft_strchr(cmd, '/'))
		path = ft_strdup(cmd);
	else
		path = path_env(my_getenv_for_path(msh), cmd);
	if (!path)
		return (NULL);
	return (path);
}
