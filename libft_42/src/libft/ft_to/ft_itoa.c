/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliu <lliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:16:08 by lliu              #+#    #+#             */
/*   Updated: 2022/11/03 14:44:58 by lliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n)
{
	int	len;

	if (n < 0)
		len = 1;
	else
		len = 0;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		num;
	char	*dst;

	num = ft_len(n);
	if (!n)
		return (dst = ft_strdup("0"));
	if (n == -2147483648)
		return (dst = ft_strdup("-2147483648"));
	dst = (char *)malloc(sizeof(char) * (num + 1));
	if (!dst)
		return (NULL);
	if (n < 0)
	{
		n *= -1;
		dst[0] = '-';
	}
	dst[num] = 0;
	while (n)
	{
		dst[--num] = n % 10 + '0';
		n = n / 10;
	}
	return (dst);
}
