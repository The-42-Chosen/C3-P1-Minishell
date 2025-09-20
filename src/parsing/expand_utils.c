/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 19:47:07 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/20 17:43:38 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	get_env_var_len(char *word)
{
	size_t	i;

	if (!word)
		return (0);
	i = 0;
	while (word[i] && word[i] != ' ' && word[i] != '$' && word[i] != '\'')
	{
		i++;
	}
	return (i);
}

char	*my_getenv(t_msh *msh, char *word)
{
	int		len;
	t_env	*env;

	len = get_env_var_len(word + 1);
	env	= msh->env;
	while (env)
	{
		if (!ft_strncmp(msh->env->key, word + 1, len))
		{
			return (msh->env->value);
		}
		env = env->next;
	}
	return (NULL);
}
