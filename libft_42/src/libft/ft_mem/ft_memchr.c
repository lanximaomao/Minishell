/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliu <lliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 18:10:41 by lliu              #+#    #+#             */
/*   Updated: 2022/11/09 16:37:23 by lliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 内存块s的前n个字符中查找第一次出现c的位置,返回
 * 	if (!s)
		return (NULL); */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n)
	{
		if (*(unsigned char *)s == (unsigned char)c)
			return ((void *)s);
		s++;
		n--;
	}
	return (NULL);
}
