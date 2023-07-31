/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliu <lliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:51:48 by lliu              #+#    #+#             */
/*   Updated: 2022/11/03 14:22:16 by lliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 复制内存区src的前n个字节给内存区dst，并保留之后的字符。
 * 函数库原函数memcpy有很大的问题，尤其是sizeof(dst) = n的时候，出现bug。
 * 同时，n > sizeof(dst)的时候overflow直接abort。
 * 我的自实现保留了两者的尺寸大小不变，如果溢出则截取有效的字符。未赋值\0 */
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dst1;
	const char	*src1;

	if (!dst && !src)
		return (NULL);
	dst1 = (char *)dst;
	src1 = (const char *)src;
	while (n--)
		*dst1++ = *src1++;
	return (dst);
}
