/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_noarg_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ep <ep@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 05:39:55 by ep                #+#    #+#             */
/*   Updated: 2025/09/26 03:34:10 by ep               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	build_env_entry_with_value(char **env_to_sort, t_env *tmp, int i)
{
	char	*tmp_key_equal;

	tmp_key_equal = ft_strjoin(tmp->key, "=");
	if (!tmp_key_equal)
		return (false);
	env_to_sort[i] = ft_strjoin(tmp_key_equal, tmp->value);
	free(tmp_key_equal);
	if (!env_to_sort[i])
		return (false);
	return (true);
}

bool	build_env_entry_no_value(char **env_to_sort, t_env *tmp, int i)
{
	env_to_sort[i] = ft_strdup(tmp->key);
	if (!env_to_sort[i])
		return (false);
	return (true);
}

void	sort_env_array(char **env_to_sort, int len)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - 1 - i)
		{
			if (ft_strcmp(env_to_sort[j], env_to_sort[j + 1]) > 0)
			{
				tmp = env_to_sort[j];
				env_to_sort[j] = env_to_sort[j + 1];
				env_to_sort[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_and_free_array(char **env_to_sort, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		ft_fprintf(1, "export %s\n", env_to_sort[i]);
		free(env_to_sort[i]);
		i++;
	}
	free(env_to_sort);
}
