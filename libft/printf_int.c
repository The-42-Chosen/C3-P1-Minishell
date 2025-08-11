/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ep <ep@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:47:43 by erpascua          #+#    #+#             */
/*   Updated: 2025/06/17 00:38:44 by ep               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	printf_int(int n)
{
	long	nb;
	int		written;
	int		tmp;

	nb = (long)n;
	written = 0;
	if (nb < 0)
	{
		if (printf_char('-') < 0)
			return (-1);
		nb = -nb;
		written = 1;
	}
	if (nb >= 10)
	{
		tmp = printf_int((int)(nb / 10));
		if (tmp < 0)
			return (-1);
		written += tmp;
	}
	if (printf_char((int)(nb % 10) + '0') < 0)
		return (-1);
	return (written + 1);
}
