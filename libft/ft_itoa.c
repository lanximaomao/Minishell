/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linlinsun <linlinsun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:58:47 by lsun              #+#    #+#             */
/*   Updated: 2023/02/19 18:34:05 by linlinsun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int		digit;
	long	ln;
	char	*str;

	ln = (long int)n;
	digit = ft_digit_num(ln);
	str = (char *)malloc(sizeof(char) * (digit + 1));
	if (!str)
		return (NULL);
	str[digit] = '\0';
	if (ln < 0)
	{
		str[0] = '-';
		ln = ln * (-1);
	}
	while (ln >= 10 && digit > 0)
	{
		str[digit - 1] = ln % 10 + 48;
		ln = ln / 10;
		digit--;
	}
	if (ln < 10)
		str[digit - 1] = ln % 10 + 48;
	return (str);
}
