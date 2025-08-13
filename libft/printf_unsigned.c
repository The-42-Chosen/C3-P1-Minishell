/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_unsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ep <ep@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:47:43 by erpascua          #+#    #+#             */
/*   Updated: 2025/06/17 00:38:44 by ep               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	printf_unsigned(unsigned int n)
{
	int	written;

	written = 0;
	if (n >= 10)
		written += printf_unsigned(n / 10);
	if (written < 0)
		return (-1);
	if (printf_char((n % 10) + '0') < 0)
		return (-1);
	return (written + 1);
}
