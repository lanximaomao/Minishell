/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:56:45 by lsun              #+#    #+#             */
/*   Updated: 2022/11/30 11:56:48 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check_format(va_list ap, char c)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_putchar_printf(va_arg(ap, int), 1);
	else if (c == 's')
		count += ft_putstr_printf(va_arg(ap, char *), 1);
	else if (c == 'd' || c == 'i')
		count += ft_putnbr_printf(va_arg(ap, int), 1);
	else if (c == 'u')
		count += ft_putnbr_unsigned_printf(va_arg(ap, unsigned long), 1);
	else if (c == 'X')
		count += ft_hexa_deci_big(va_arg(ap, int));
	else if (c == 'x')
		count += ft_hexa_deci_small(va_arg(ap, int));
	else if (c == 'p')
		count += ft_printf_ptr(va_arg(ap, unsigned long long));
	else if (c == '%')
		count += ft_putchar_printf('%', 1);
	return (count);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		count;
	va_list	ap;

	if (!str)
		return (0);
	i = 0;
	count = 0;
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] != '\0')
		{
			count += ft_check_format(ap, str[i + 1]);
			i++;
		}
		else
			count += ft_putchar_printf(str[i], 1);
		i++;
	}
	va_end(ap);
	return (count);
}
