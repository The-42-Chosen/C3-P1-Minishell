/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ep <ep@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:10:56 by erpascua          #+#    #+#             */
/*   Updated: 2025/06/17 00:38:44 by ep               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	is_fmt(int c)
{
	static const char	*fmt_lst = "cspdiuxX%";
	size_t				i;

	i = 0;
	while (fmt_lst[i])
	{
		if (fmt_lst[i] == (char)c)
			return ((char)c);
		i++;
	}
	return (0);
}

static int	interpretor(const char **fmt, va_list args)
{
	int	written;

	written = 0;
	if (**fmt == 'c')
		written = printf_char(va_arg(args, int));
	else if (**fmt == 's')
		written = printf_str(va_arg(args, char *));
	else if (**fmt == 'p')
		written = printf_address(va_arg(args, void *));
	else if (**fmt == 'd' || **fmt == 'i')
		written = printf_int(va_arg(args, int));
	else if (**fmt == 'u')
		written = printf_unsigned(va_arg(args, unsigned int));
	else if (**fmt == 'x')
		written = printf_hex_low(va_arg(args, unsigned int));
	else if (**fmt == 'X')
		written = printf_hex_upp(va_arg(args, unsigned int));
	else if (**fmt == '%')
		written = printf_percent();
	return (written);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, fmt);
	if (!fmt)
		return (-1);
	while (*fmt)
	{
		if (*fmt == '%' && is_fmt(*(fmt + 1)))
		{
			fmt++;
			count += interpretor(&fmt, args);
			fmt++;
		}
		else
		{
			write(1, fmt, 1);
			count++;
			fmt++;
		}
	}
	va_end(args);
	return (count);
}
