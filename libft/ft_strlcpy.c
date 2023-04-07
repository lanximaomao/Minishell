/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 09:39:49 by lsun              #+#    #+#             */
/*   Updated: 2022/11/14 12:55:10 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	char	*src_;

	src_ = (char *)src;
	if (!dstsize)
		return (ft_strlen((const char *)src_));
	if (*src_ == '\0')
		*dst = '\0';
	while (dstsize > 1 && *src_ != '\0')
	{
		*dst = *src_;
		dst++;
		src_++;
		dstsize--;
	}
	*dst = '\0';
	return (ft_strlen((const char *)src));
}
