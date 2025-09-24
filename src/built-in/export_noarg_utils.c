/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_noarg_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ep <ep@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 05:39:55 by ep                #+#    #+#             */
/*   Updated: 2025/09/23 05:42:20 by ep               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	order_tab(char **env_to_sort, int len)
{
	sort_env_array(env_to_sort, len);
	print_and_free_array(env_to_sort, len);
}

int	lst_len(t_env *env)
{
	t_env	*tmp;
	int		len;

	tmp = env;
	len = 0;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}
