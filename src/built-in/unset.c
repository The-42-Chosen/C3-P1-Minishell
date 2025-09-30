/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 19:05:40 by erpascua          #+#    #+#             */
/*   Updated: 2025/09/29 00:18:51 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_first_node(t_msh *msh, t_env *node)
{
	msh->env = node->next;
	free(node->key);
	free(node->value);
	free(node);
}

static void	unset_middle_node(t_env *prev, t_env *node)
{
	prev->next = node->next;
	free(node->key);
	free(node->value);
	free(node);
}

static void	unset_variable(t_msh *msh, char *var_name)
{
	t_env	*tmp;

	tmp = msh->env;
	if (tmp && ft_strncmp(var_name, tmp->key, ft_strlen(var_name) + 1) == 0)
	{
		unset_first_node(msh, tmp);
		return ;
	}
	while (tmp && tmp->next)
	{
		if (ft_strncmp(var_name, tmp->next->key, ft_strlen(var_name) + 1) == 0)
		{
			unset_middle_node(tmp, tmp->next);
			break ;
		}
		tmp = tmp->next;
	}
}

int	bi_unset(t_msh *msh, char **av)
{
	int	i;

	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		return (0);
	i = 1;
	while (av[i])
	{
		if (!is_valid_identifier(av[i]))
		{
			ft_fprintf(2, "Billyshell: unset: `%s': not a valid identifier\n",
				av[i]);
			msh->exit_code = 1;
			return (1);
		}
		unset_variable(msh, av[i]);
		i++;
	}
	msh->exit_code = 0;
	return (0);
}
