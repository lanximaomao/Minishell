/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:30:46 by lsun              #+#    #+#             */
/*   Updated: 2022/11/16 17:49:17 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** locates the first ccurrence of c, in a string.
** a pointer to the byte located or null is returned.
*/

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*first;
	unsigned char	checker;

	i = 0;
	first = (unsigned char *)s;
	checker = (unsigned char)c;
	while (i < n)
	{
		if (first[i] == checker)
			return (&first[i]);
		i++;
	}
	return (NULL);
}
