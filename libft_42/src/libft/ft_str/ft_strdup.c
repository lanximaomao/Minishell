/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliu <lliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 18:25:02 by lliu              #+#    #+#             */
/*   Updated: 2022/11/03 14:29:07 by lliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 开辟新的内存来复制s1字符串;
 * 内部定义两个指针是为了,记录其中复制后字符串的首地址返回,否则++完之后是空值
 * 原型中使用memcpy也可以 */
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*temp;
	char	*dst;

	temp = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	dst = temp;
	while (*s1)
		*temp++ = *s1++;
	*temp = '\0';
	return (dst);
}
