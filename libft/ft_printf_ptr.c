/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:57:02 by lsun              #+#    #+#             */
/*   Updated: 2022/11/30 11:57:04 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_hexa_deci_ptr(unsigned long long n)
{
	int	temp;
	int	count;

	count = 1;
	if (n / 16 > 0)
	{
		count += ft_hexa_deci_ptr(n / 16);
	}
	temp = n % 16;
	if (temp > 9)
		temp = temp - 10 + 'a';
	else
		temp += '0';
	ft_putchar_printf(temp, 1);
	return (count);
}

int	ft_printf_ptr(unsigned long long n)
{
	int	count;

	count = 2;
	ft_putchar_printf('0', 1);
	ft_putchar_printf('x', 1);
	count += ft_hexa_deci_ptr(n);
	return (count);
}
