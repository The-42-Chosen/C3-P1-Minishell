/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 16:34:38 by erpascua          #+#    #+#             */
/*   Updated: 2025/09/26 16:37:56 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_destroy(t_env *env)
{
	t_env	*tmp;
	t_env	*next;

	while (env)
	{
		tmp = env;
		next = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		env = next;
	}
}

void	free_msh(t_msh *msh)
{
	free(msh->data);
	free(msh->entry);
	free(msh->history);
	stack_destroy(msh->stack);
	env_destroy(msh->env);
}

void	free_msh_builtins(t_msh *msh)
{
	int	i;

	i = 0;
	while (i < NB_BUILTINS)
	{
		free(msh->builtin_names[i]);
		i++;
	}
}
