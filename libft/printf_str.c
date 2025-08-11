/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ep <ep@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:14:29 by erpascua          #+#    #+#             */
/*   Updated: 2025/06/17 00:38:44 by ep               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	printf_str(char *s)
{
	size_t	len;
	int		tmp;

	if (!s)
	{
		if (write(1, "(null)", 6) < 0)
			return (-1);
		return (6);
	}
	len = pf_strlen(s);
	while (*s)
	{
		tmp = printf_char(*s++);
		if (tmp < 0)
			return (-1);
	}
	return ((int)len);
}
