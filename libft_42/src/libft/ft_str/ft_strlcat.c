/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliu <lliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:08:00 by lliu              #+#    #+#             */
/*   Updated: 2022/11/10 17:54:36 by lliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 连接字符串，将长度有限的src连接到dst字符串后面。
 * 需要考虑的东西太多了:1. 返回值,是字符串长度dst+src相加,但是当dstsize < src长度时,取小者
 * 2.dstsize实际包含了\0, 与strlcpy一致;
 * 3.size_t为无符号正数,按理说不需要考虑0和负数的情况,在原型中直接abort而自实现中返回负值*/

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (dst == (void *)0 && !size)
		return (ft_strlen(src));
	while (dst[i] && i < size)
		i++;
	while (src[j] && (i + j + 1) < size)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i < size)
		dst[i + j] = '\0';
	return (i + ft_strlen(src));
}
