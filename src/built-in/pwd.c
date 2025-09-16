/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ep <ep@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 19:02:46 by erpascua          #+#    #+#             */
/*   Updated: 2025/09/16 07:15:57 by ep               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_pwd(char **argv)
{
	int		i;
	char	*buf;

	(void)argv;
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
