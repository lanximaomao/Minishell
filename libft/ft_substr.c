/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:15:40 by lsun              #+#    #+#             */
/*   Updated: 2022/11/17 12:15:42 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	sub_len;
	size_t	i;
	char	*substr;

	if (!s)
		return (NULL);
	i = 0;
	s_len = ft_strlen(s);
	if (start >= s_len)
		sub_len = 0;
	else if (len <= s_len - start)
		sub_len = len;
	else
		sub_len = s_len - start;
	substr = (char *)malloc(sub_len * sizeof(char) + 1);
	if (!substr)
		return (NULL);
	while (sub_len > 0 && i < sub_len)
	{
		substr[i] = s[i + start];
		i++;
	}
	substr[sub_len] = '\0';
	return (substr);
}
