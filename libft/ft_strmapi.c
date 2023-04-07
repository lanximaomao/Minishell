/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:22:56 by lsun              #+#    #+#             */
/*   Updated: 2022/11/04 15:21:46 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str_f;
	int		len;
	int		i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	str_f = (char *)malloc(sizeof(char) * len + 1);
	if (!str_f)
		return (NULL);
	while (i < len)
	{
		str_f[i] = f(i, s[i]);
		i++;
	}
	str_f[i] = '\0';
	return (str_f);
}
