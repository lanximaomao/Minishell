/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliu <lliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 19:47:09 by lliu              #+#    #+#             */
/*   Updated: 2023/04/18 19:50:43 by lliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	new_ptr = NULL;
	if (!new_size)
	{
		free(ptr);
		ptr = NULL;
		return (NULL);
	}
	new_ptr = (void *)ft_calloc(new_size, sizeof(void));
	if (!new_ptr)
		return (NULL);
	if (ptr != NULL)
	{
		ft_memcpy(new_ptr, ptr, old_size);
		free(ptr);
		ptr = NULL;
	}
	return (new_ptr);
}
