/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 17:26:54 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/23 21:11:42 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_len_env(t_env *env)
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

static int	free_env_entries(char ***env, int *i)
{
	while (*i-- > 0)
		free(env[*i]);
	free(env);
	return (0);
}

static char	**built_env_entry(t_msh *msh, char **env)
{
	t_env	*tmp;
	int		i;
	char	*stock;

	tmp = msh->env;
	i = 0;
	while (tmp)
	{
		stock = ft_strjoin(tmp->key, "=");
		if (!stock)
			return (free_env_entries(&env, &i), NULL);
		if (tmp->value)
			env[i] = ft_strjoin(stock, tmp->value);
		else
			env[i] = ft_strjoin(stock, "");
		free(stock);
		if (!env[i])
			return (free_env_entries(&env, &i), NULL);
		tmp = tmp->next;
		i++;
	}
	return (env[i] = NULL, env);
}

char	**msh_getenv(t_msh *msh)
{
	char	**env;

	env = malloc(sizeof(char *) * (get_len_env(msh->env) + 1));
	if (!env)
		return (NULL);
	return (built_env_entry(msh, env));
}
