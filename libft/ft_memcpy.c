/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 13:37:33 by lsun              #+#    #+#             */
/*   Updated: 2022/11/10 16:14:03 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** fill a byte string with a byte given by c
** overflow if len exceed the buffer size
*/

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*dst_;
	char	*src_;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	dst_ = (char *)dst;
	src_ = (char *)src;
	while (i < len)
	{
		dst_[i] = src_[i];
		i++;
	}
	return (dst_);
}
