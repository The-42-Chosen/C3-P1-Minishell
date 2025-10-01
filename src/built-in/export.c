/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 19:04:02 by erpascua          #+#    #+#             */
/*   Updated: 2025/10/01 16:40:06 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	build_env_array(char **env_to_sort, t_env *env)
{
	t_env	*tmp;
	int		i;
	bool	success;

	tmp = env;
	i = 0;
	while (tmp)
	{
		if (tmp->value)
			success = build_env_entry_with_value(env_to_sort, tmp, i);
		else
			success = build_env_entry_no_value(env_to_sort, tmp, i);
		if (!success)
			return (false);
		i++;
		tmp = tmp->next;
	}
	return (true);
}

static void	export_no_arg(t_env *env)
{
	char	**env_to_sort;
	int		len_env;

	len_env = lst_len(env);
	env_to_sort = malloc((len_env + 1) * sizeof(char *));
	if (!env_to_sort)
		return ;
	if (!build_env_array(env_to_sort, env))
		return (free_tab(env_to_sort));
	order_tab(env_to_sort, len_env);
	return ;
}

static void	export_var_no_value(t_msh *msh, char *arg)
{
	t_env	*new_node;
	bool	is_found;

	is_found = export_replace_value_no_val(msh->env, arg);
	if (!is_found)
	{
		new_node = create_env_node_no_value(arg);
		if (new_node)
			export_create_keyvalue(msh, new_node);
	}
}

static void	export_update_env(t_msh *msh, char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_strchr(av[i], '='))
			export_var_with_value(msh, av[i]);
		else
			export_var_no_value(msh, av[i]);
		i++;
	}
}

int	bi_export(t_msh *msh, char **av)
{
	int	i;

	(void)msh;
	if (!av || !*av)
		return (1);
	i = 1;
	while (av[i])
	{
		if (!is_valid_identifier(av[i]))
		{
			ft_fprintf(2, "Billyshell: export: `%s': not a valid identifier\n",
				av[i]);
			return (msh->exit_code = 1, msh->exit_code);
		}
		i++;
	}
	if (i == 1)
		export_no_arg(msh->env);
	else
	{
		if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
			return (0);
		export_update_env(msh, av);
	}
	return (msh->exit_code = 0, 0);
}
