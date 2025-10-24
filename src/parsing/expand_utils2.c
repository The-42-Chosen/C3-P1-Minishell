/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:54:01 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/24 13:56:47 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	var_len(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (ft_isalnum(s[i]) || s[i] == '_')
		i++;
	return (i);
}

static char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (!res)
		return (NULL);
	free(s1);
	free(s2);
	return (res);
}

static char	*process_variable(t_msh *msh, char *s, int *i, char *res)
{
	char	*before;
	int		len;

	before = ft_substr(s, 0, *i);
	res = ft_strjoin_free(res, before);
	if (!res)
		return (NULL);
	len = 1 + var_len(s + *i + 1);
	if (s[*i + 1] == '?')
		len = 2;
	before = ft_substr(s, *i, len);
	if (!before)
		return (free(res), NULL);
	res = ft_strjoin_free(res, replace_env_var(msh, before));
	return (res);
}

static char	*handle_dollar(t_msh *msh, char **s, int *i, char *res)
{
	int	len;

	len = 1 + var_len(*s + *i + 1);
	if ((*s)[*i + 1] == '?')
		len = 2;
	res = process_variable(msh, *s, i, res);
	if (!res)
		return (NULL);
	*s += *i + len;
	*i = 0;
	return (res);
}

char	*expand_all_vars(t_msh *msh, char *s)
{
	char	*res;
	char	*tmp;
	int		i;

	res = ft_strdup("");
	if (!res)
		return (NULL);
	tmp = s;
	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			res = handle_dollar(msh, &s, &i, res);
			if (!res)
				return (free(tmp), NULL);
		}
		else
			i++;
	}
	if (*s)
		res = ft_strjoin_free(res, ft_strdup(s));
	return (free(tmp), res);
}
