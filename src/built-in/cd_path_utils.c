/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_path_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:53:33 by erpascua          #+#    #+#             */
/*   Updated: 2025/10/03 16:54:30 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*unify_path(t_paths *paths, char *folder)
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
