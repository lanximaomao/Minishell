/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 09:32:45 by lsun              #+#    #+#             */
/*   Updated: 2022/11/17 13:06:19 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	k;

	if (!dst && !src)
		return (0);
	if (dstsize == 0)
		return (ft_strlen((char *)(src)));
	i = ft_strlen(dst);
	j = 0;
	k = i;
	if (dstsize <= i)
		return (ft_strlen((char *)(src)) + dstsize);
	while (dstsize > i + 1 && src[j] != '\0')
	{
		dst[i++] = src[j++];
	}
	dst[i] = '\0';
	return (k + ft_strlen((char *)(src)));
}
