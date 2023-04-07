/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 09:33:08 by lsun              #+#    #+#             */
/*   Updated: 2022/11/01 15:21:05 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	if (src > dst)
	{
		while (len > i)
		{
			((char *)dst)[i] = ((char *)src)[i];
			i++;
		}
	}
	i = 0;
	if (src <= dst)
	{
		while (len > i)
		{
			((char *)dst)[len - 1 - i] = ((char *)src)[len - 1 - i];
			i++;
		}
	}
	return ((char *)dst);
}
