/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliu <lliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:00:50 by lliu              #+#    #+#             */
/*   Updated: 2023/06/04 15:42:36 by lliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
// utils
static int	ft_len_uitoa(unsigned int n)
{
	int	len;

	len = 0;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_uitoa(unsigned int n)
{
	int		num;
	char	*dst;

	num = ft_len_uitoa(n);
	dst = (char *)malloc(sizeof(char) * (num + 1));
	if (!dst)
		return (NULL);
	dst[num] = 0;
	while (n)
	{
		dst[--num] = n % 10 + '0';
		n = n / 10;
	}
	return (dst);
}

static int	ft_format(va_list args_ptr, char cur_ch)
{
	int	len_print;

	len_print = 0;
	if (cur_ch == 'c')
		len_print += ft_printchr(va_arg(args_ptr, int));
	if (cur_ch == 's')
		len_print += ft_printstr(va_arg(args_ptr, char *));
	if (cur_ch == 'p')
		len_print += ft_printptr(va_arg(args_ptr, unsigned long int));
	if (cur_ch == 'd' || cur_ch == 'i')
		len_print += ft_printnbr(va_arg(args_ptr, int));
	if (cur_ch == 'u')
		len_print += ft_printunsigned(va_arg(args_ptr, unsigned int));
	if (cur_ch == 'x' || cur_ch == 'X')
		len_print += ft_printhex(va_arg(args_ptr, unsigned int), cur_ch);
	if (cur_ch == '%')
		len_print += ft_printpercent();
	return (len_print);
}

int	ft_printf(const char *str, ...)
{
	int		len_print;
	char	cur_ch;
	va_list	args_ptr;

	len_print = 0;
	va_start(args_ptr, str);
	cur_ch = *(str++);
	while (cur_ch)
	{
		if (cur_ch == '%')
		{
			cur_ch = *(str++);
			len_print += ft_format(args_ptr, cur_ch);
		}
		else
			len_print += ft_printchr(cur_ch);
		cur_ch = *(str++);
	}
	va_end(args_ptr);
	return (len_print);
}
