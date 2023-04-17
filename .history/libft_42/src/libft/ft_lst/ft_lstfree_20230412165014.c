/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliu <lliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:49:53 by lliu              #+#    #+#             */
/*   Updated: 2023/04/12 16:50:14 by lliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_l(t_list *stack_a)
{
	t_list	*del;
	t_list	*next;

	del = stack_a;
	while (del)
	{
		next = del->next;
		free(del);
		del = next;
	}
}
