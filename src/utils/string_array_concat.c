/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_array_concat.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:02:32 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/02 19:28:08 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**string_array_concat(char **sa1, char **sa2)
{
	char	**res;
	int		i;
	int		j;

	res = calloc(ft_strlen(*sa1) + ft_strlen(*sa2) + 1, sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (sa1[i])
	{
		res[i] = ft_strdup(sa1[i]);
		if (!res[i])
			return (free_tab(res), NULL);
		i++;
	}
	j = 0;
	while (sa2[j])
	{
		res[i] = ft_strdup(sa2[j]);
		if (!res[i])
			return (free_tab(res), NULL);
		j++;
		i++;
	}
	return (res[i] = 0, res);
}
