/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliu <lliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:49:53 by lliu              #+#    #+#             */
/*   Updated: 2023/04/12 16:51:08 by lliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Free all the linked list */

void	lst_free(t_list *lst)
{
	t_list	*del;
	t_list	*next;

	del = lst;
	while (del)
	{
		next = del->next;
		free(del);
		del = next;
	}
}
