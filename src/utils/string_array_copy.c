/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_array_copy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 10:41:00 by gpollast          #+#    #+#             */
/*   Updated: 2025/09/23 13:43:21 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_string_array(char **s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	**string_array_copy(char **s)
{
	char	**copy;
	int		len;
	int		i;
	
	len = len_string_array(s);
	copy = malloc(sizeof(char *) * (len + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		copy[i] = ft_strdup(s[i]);
		if (!copy[i])
		{
			free_tab(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = 0;
	return (copy);
}
