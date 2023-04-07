/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 11:00:15 by lsun              #+#    #+#             */
/*   Updated: 2022/11/17 13:40:27 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*start;

	if (count == 0 || size == 0)
		return (ft_calloc(1, 1));
	if (count * size / size != count)
		return (NULL);
	start = (void *)malloc(size * count);
	if (!start)
		return (NULL);
	ft_bzero(start, size * count);
	return (start);
}
