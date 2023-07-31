/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliu <lliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:19:34 by lliu              #+#    #+#             */
/*   Updated: 2022/11/10 11:38:41 by lliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_maxmin(const char *str, int atoi, int c)
{
	if (atoi == 214748364)
	{
		if ((*str == 56 && c != -1) || *str == 57)
			return (-1);
		if (c == -1 && *str == 57)
			return (0);
	}
	if ((atoi > 214748364 && c != -1) && (*str >= 48 && *str <= 57))
		return (-1);
	if ((atoi > 214748364 && c == -1) && (*str >= 48 && *str <= 57))
		return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	int	c;
	int	res;
	int	atoi;

	c = 1;
	atoi = 0;
	while (*str == 32 || (*str <= 13 && *str >= 9))
		str++;
	if (*str == 45)
	{
		c *= -1;
		str++;
	}
	else if (*str == 43)
		str++;
	while (*str && (*str >= 48 && *str <= 57))
	{
		atoi = atoi * 10 + (*str - '0');
		str++;
		res = ft_maxmin(str, atoi, c);
		if (res != 1)
			return (res);
	}
	return (atoi * c);
}
