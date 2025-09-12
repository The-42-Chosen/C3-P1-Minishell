/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 19:02:46 by erpascua          #+#    #+#             */
/*   Updated: 2025/09/12 14:56:11 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_pwd(void)
{
	int		i;
	char	*buf;

	i = 1;
	buf = malloc(i);
	while (getcwd(buf, i) == NULL && errno == ERANGE)
	{
		free(buf);
		i *= 2;
		buf = malloc(i);
		getcwd(buf, i);
		if (!buf)
			return (1);
	}
	ft_fprintf(1, "%s\n", buf);
	free(buf);
	return (0);
}
