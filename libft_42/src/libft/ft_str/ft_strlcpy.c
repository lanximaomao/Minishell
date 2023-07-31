/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliu <lliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:51:53 by lliu              #+#    #+#             */
/*   Updated: 2022/11/09 11:12:38 by lliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* test notice: dst/src empty; dstsize = 0;
 * 安全函数，将src中的前dstsize个字符复制到dst，用dstsize来控制溢出，保证无字符串溢出
 * 相比于strcpy无缓冲区越界考量,strncpy不保证\0
 * dstsize中考虑了\0的位置,所以在dst字符串大小不够的情况向,其实是将src的前dstsize-1的字符复制
 * 原型中不考虑n为负数
 * 自实现中错误信息为返回值-1,乱码*/

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	int		n;

	i = 0;
	n = ft_strlen(src);
	if (!dstsize)
		return (n);
	if (!n)
	{
		dst[i] = '\0';
		return (n);
	}
	while (i < dstsize - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (n);
}
