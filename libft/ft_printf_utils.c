/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:56:55 by lsun              #+#    #+#             */
/*   Updated: 2022/11/30 11:56:57 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_printf(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_putstr_printf(char *s, int fd)
{
	int	i;
	int	count;

	count = 0;
	if (s == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
		count++;
	}
	return (count);
}

int	ft_putnbr_printf(int n, int fd)
{
	int	count;

	count = 1;
	if (n < 0 && n != -2147483648)
	{
		ft_putchar_printf('-', fd);
		n = n * (-1);
		count++;
	}
	if (n == -2147483648)
	{
		ft_putchar_printf('-', fd);
		ft_putchar_printf('0' + 2, fd);
		count += 2;
		n = 147483648;
	}
	if (n >= 10)
	{
		count += ft_putnbr_printf(n / 10, fd);
	}
	ft_putchar_printf(n % 10 + 48, fd);
	return (count);
}

int	ft_putnbr_unsigned_printf(unsigned int n, int fd)
{
	int	count;

	count = 1;
	if (n >= 10)
	{
		count += ft_putnbr_unsigned_printf(n / 10, fd);
	}
	ft_putchar_printf(n % 10 + 48, fd);
	return (count);
}
