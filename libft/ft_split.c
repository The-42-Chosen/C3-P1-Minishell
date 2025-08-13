/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:53:47 by erpascua          #+#    #+#             */
/*   Updated: 2025/07/28 17:46:46 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	word_count(char const *s, char c)
{
	size_t	wc;
	size_t	i;

	wc = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
		{
			wc++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (wc);
}

static char	**tab_free(char **tab, size_t j)
{
	while (j--)
		free(tab[j]);
	free(tab);
	return (NULL);
}

char	**spliter(char const *s, char c, char **tab)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
		{
			start = i;
			while (s[i] != c && s[i])
				i++;
			tab[j] = (char *)malloc((i - start + 1) * sizeof(char));
			if (!tab[j])
				return (tab_free(tab, j));
			ft_memcpy(tab[j], s + start, i - start);
			tab[j][i - start] = 0;
			j++;
		}
	}
	tab[j] = 0;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = (char **)malloc((word_count(s, c) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	return (spliter(s, c, tab));
}
