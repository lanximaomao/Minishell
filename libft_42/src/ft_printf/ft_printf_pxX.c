/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_pxX.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliu <lliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:01:02 by lliu              #+#    #+#             */
/*   Updated: 2023/02/22 14:17:46 by lliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_hex(unsigned long int ptr, char x)
{
	int					len_print;
	unsigned long int	temp;

	len_print = 0;
	temp = ptr;
	while (temp)
	{
		temp = temp / 16;
		len_print++;
	}
	if (ptr >= 16)
	{
		ft_hex(ptr / 16, x);
		ft_hex(ptr % 16, x);
	}
	else
	{
		if (ptr >= 10)
			ft_printchr(ptr - 10 + x);
		else
			ft_printchr(ptr + '0');
	}
	return (len_print);
}

int	ft_printptr(unsigned long int ptr)
{
	int	len_print;

	len_print = write(1, "0x", 2);
	if (!ptr)
		len_print += write(1, "0", 1);
	else
		len_print += ft_hex(ptr, 'a');
	return (len_print);
}

int	ft_printhex(unsigned int n, char cur_ch)
{
	int	len_print;

	len_print = 0;
	if (!n)
		return (write(1, "0", 1));
	if (cur_ch == 'x')
		len_print += ft_hex((unsigned long int)n, 'a');
	if (cur_ch == 'X')
		len_print += ft_hex((unsigned long int)n, 'A');
	return (len_print);
}
