/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa_deci.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:57:10 by lsun              #+#    #+#             */
/*   Updated: 2022/11/30 11:57:13 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexa_deci_big(unsigned int n)
{
	int	temp;
	int	count;

	count = 1;
	if (n / 16 > 0)
	{
		count += ft_hexa_deci_big(n / 16);
	}
	temp = n % 16;
	if (temp > 9)
		temp = temp - 10 + 'A';
	else
		temp += '0';
	ft_putchar_printf(temp, 1);
	return (count);
}

int	ft_hexa_deci_small(unsigned int n)
{
	int	temp;
	int	count;

	count = 1;
	if (n / 16 > 0)
	{
		count += ft_hexa_deci_small(n / 16);
	}
	temp = n % 16;
	if (temp > 9)
		temp = temp - 10 + 'a';
	else
		temp += '0';
	ft_putchar_printf(temp, 1);
	return (count);
}
