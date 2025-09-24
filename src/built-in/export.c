/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 19:04:02 by erpascua          #+#    #+#             */
/*   Updated: 2025/09/24 14:40:35 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_no_arg(t_env *env)
{
	t_env	*tmp;
	char	*tmp_key_equal;
	char	**env_to_sort;
	int		i;
	int		len_env;

	len_env = lst_len(env);
	tmp = env;
	i = 0;
	env_to_sort = malloc((len_env + 1) * sizeof(char *));
	while (tmp)
	{
		if (tmp->value)
		{
			tmp_key_equal = ft_strjoin(tmp->key, "=");
			env_to_sort[i] = ft_strjoin(tmp_key_equal, tmp->value);
			free(tmp_key_equal);
		}
		else
			env_to_sort[i] = ft_strdup(tmp->key);
		i++;
		tmp = tmp->next;
	}
	order_tab(env_to_sort, len_env);
	return ;
}

static bool	is_valid_identifier(char *s)
{
	if (!s || !*s)
		return (0);
	if (!(ft_isalpha(*s) || *s == '_'))
		return (0);
	s++;
	while (*s && *s != '=')
	{
		if (!(ft_isalnum(*s) || *s == '_'))
			return (0);
		s++;
	}
	return (1);
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
			msh->exit_code = 1;
			return (msh->exit_code);
		}
		i++;
	}
	if (i == 1)
		export_no_arg(msh->env);
	else
		export_update_env(msh, av);
	return (0);
}
