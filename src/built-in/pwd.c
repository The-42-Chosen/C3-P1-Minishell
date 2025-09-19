/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ep <ep@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 19:02:46 by erpascua          #+#    #+#             */
/*   Updated: 2025/09/17 02:47:53 by ep               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_pwd(t_msh *msh, char **av)
{
	int		i;
	char	*buf;

	(void)msh;
	(void)av;
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
