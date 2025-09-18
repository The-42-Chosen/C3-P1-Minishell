/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 19:47:07 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/18 19:48:25 by gpollast         ###   ########.fr       */
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
	int	i;
	int	len;

	i = 0;
	len = get_env_var_len(word + 1);
	while (msh->env[i])
	{
		if (!ft_strncmp(msh->env[i], word + 1, len) && msh->env[i][len] == '=')
		{
			return (msh->env[i] + len + 1);
		}
		i++;
	}
	return (NULL);
}
