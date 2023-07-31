/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_csdiu%.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliu <lliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:54:32 by lliu              #+#    #+#             */
/*   Updated: 2023/02/22 14:17:41 by lliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printchr(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_printstr(char *str)
{
	int		i;
	char	*str_null;

	i = 0;
	str_null = "(null)";
	if (str == NULL)
	{
		while (str_null[i])
		{
			ft_printchr(str_null[i]);
			i++;
		}
		return (i);
	}
	while (str[i])
	{
		ft_printchr(str[i]);
		i++;
	}
	return (i);
}

int	ft_printnbr(int nb)
{
	int		len_print;
	char	*num_itoa;

	num_itoa = ft_itoa(nb);
	len_print = ft_printstr(num_itoa);
	if (!num_itoa)
		return (len_print);
	free(num_itoa);
	return (len_print);
}

int	ft_printunsigned(unsigned int n)
{
	int		len_print;
	char	*num_uitoa;

	len_print = 0;
	if (n > 0)
	{
		num_uitoa = ft_uitoa(n);
		len_print = ft_printstr(num_uitoa);
		if (!num_uitoa)
			return (len_print);
		free(num_uitoa);
	}
	if (!n)
		len_print += write(1, "0", 1);
	return (len_print);
}

int	ft_printpercent(void)
{
	write(1, "%", 1);
	return (1);
}
