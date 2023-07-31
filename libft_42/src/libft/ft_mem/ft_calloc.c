/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliu <lliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:21:15 by lliu              #+#    #+#             */
/*   Updated: 2023/01/15 18:41:31 by lliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*addr;

	if (!count || !size)
		return (ft_calloc(1, 1));
	if (count * size / size != count)
		return (NULL);
	addr = malloc(count * size);
	if (!addr)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		addr[i] = 0;
		i++;
	}
	return (addr);
}
