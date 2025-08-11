/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ep <ep@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:47:47 by erpascua          #+#    #+#             */
/*   Updated: 2025/06/17 00:38:44 by ep               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	put_ptr(uintptr_t n)
{
	int	written;
	int	tmp;

	if (n >= 16)
	{
		written = put_ptr(n / 16);
		if (written < 0)
			return (-1);
		tmp = put_ptr(n % 16);
		if (tmp < 0)
			return (-1);
		return (written + tmp);
	}
	if (n <= 9)
		return (printf_char('0' + (int)n));
	return (printf_char('a' + (int)(n - 10)));
}

int	printf_address(void *ptr)
{
	int	tmp;

	if (ptr == NULL)
		return (printf_str("(nil)"));
	if (printf_str("0x") < 0)
		return (-1);
	tmp = put_ptr((uintptr_t)ptr);
	if (tmp < 0)
		return (-1);
	return (2 + tmp);
}
