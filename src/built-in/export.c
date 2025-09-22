/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ep <ep@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 19:04:02 by erpascua          #+#    #+#             */
/*   Updated: 2025/09/22 21:21:13 by ep               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	order_tab(char **env_to_sort, int len)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < len - 1)
	{
		if (ft_strcmp(env_to_sort[i], env_to_sort[i + 1]) > 0)
		{
			tmp = ft_strdup(env_to_sort[i]);
			env_to_sort[i] = NULL;
			env_to_sort[i] = ft_strdup(env_to_sort[i + 1]);
			env_to_sort[i + 1] = NULL;
			env_to_sort[i + 1] = ft_strdup(tmp);
			free(tmp);
			i = 0;
		}
		i++;
	}
	i = 1;
	while (i < len)
	{
		ft_fprintf(1, "export %s\n", env_to_sort[i]);
		i++;
	}
	free(env_to_sort);
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
		tmp_key_equal = ft_strjoin(tmp->key, "=");
		env_to_sort[i] = ft_strjoin(tmp_key_equal, tmp->value);
		free(tmp_key_equal);
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
			ft_fprintf(2, "minishell: export: `%s': not a valid identifier\n",
				av[i]);
			return (1);
		}
		i++;
	}
	if (i == 1)
		export_no_arg(msh->env);
	return (0);
}
