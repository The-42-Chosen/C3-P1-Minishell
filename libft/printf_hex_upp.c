/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_hex_upp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ep <ep@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 02:09:49 by ep                #+#    #+#             */
/*   Updated: 2025/06/17 00:38:44 by ep               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	printf_hex_upp(unsigned int n)
{
	int	div;
	int	mod;

	if (n == 0)
		return (printf_char('0'));
	if (n >= 16)
	{
		div = printf_hex_upp(n / 16);
		if (div < 0)
			return (-1);
		mod = printf_hex_upp(n % 16);
		if (mod < 0)
			return (-1);
		return (div + mod);
	}
	if (n <= 9)
		return (printf_char('0' + n));
	return (printf_char('A' + (n - 10)));
}
