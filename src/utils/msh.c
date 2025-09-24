/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 17:26:54 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/23 13:43:21 by gpollast         ###   ########.fr       */
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

char	**msh_getenv(t_msh *msh)
{
	char	**env;
	t_env	*tmp;
	int		i;
	char	*stock;

	env = malloc(sizeof(char *) * (get_len_env(msh->env) + 1));
	if (!env)
		return (NULL);
	tmp = msh->env;
	i = 0;
	while (tmp)
	{
		stock = ft_strjoin(tmp->key, "=");
		env[i] = ft_strjoin(stock, tmp->value);
		free(stock);
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}
