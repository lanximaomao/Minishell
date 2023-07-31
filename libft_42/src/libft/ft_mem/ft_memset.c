/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliu <lliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:47:03 by lliu              #+#    #+#             */
/*   Updated: 2022/11/01 14:31:16 by lliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 将str的前len个元素赋为c值. */
#include "libft.h"

void	*ft_memset(void *str, int c, size_t len)
{
	size_t			i;
	unsigned char	*des;

	i = 0;
	des = str;
	while (i < len)
	{
		des[i] = c;
		i++;
	}
	return (str);
}
