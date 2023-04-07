/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:14:55 by lsun              #+#    #+#             */
/*   Updated: 2022/11/14 20:31:19 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_trim_assign(char const *s1, int start, int end)
{
	char	*strim;
	int		i;

	i = 0;
	strim = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!strim)
		return (NULL);
	while (start <= end)
		strim[i++] = s1[start++];
	strim[i] = '\0';
	return (strim);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	i;
	int	check;
	int	start;
	int	end;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	start = 0;
	end = ft_strlen(s1) - 1;
	check = -1;
	while (s1[i])
	{
		if (ft_strchr(set, s1[i]) && check < 0)
			start++;
		if (!(ft_strchr(set, s1[i])) && check < 0)
			check = 1;
		if (ft_strchr(set, s1[end]) && check > 0)
			end--;
		i++;
	}
	return (ft_trim_assign(s1, start, end));
}
