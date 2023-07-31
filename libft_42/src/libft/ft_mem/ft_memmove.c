/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliu <lliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 19:11:20 by lliu              #+#    #+#             */
/*   Updated: 2022/11/01 16:56:09 by lliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 从存储区src 复制 前n 个字节到存储区dst。
 * 原型中memcpy和memmove两者的区别主要在于是否处理数据重复区域
 * 不能使用memcpy一个临时中转，这样会导致128M以上的数据无法输入，
 * 即只能len < 128*1024*1024 */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	if (src < dst)
		while (len--)
			*(char *)(dst + len) = *(const char *)(src + len);
	else
	{
		i = 0;
		while (i < len)
		{
			*(char *)(dst + i) = *(const char *)(src + i);
			i++;
		}
	}
	return (dst);
}
