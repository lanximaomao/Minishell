/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:35:41 by lsun              #+#    #+#             */
/*   Updated: 2022/12/22 15:41:04 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*joint_str;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	joint_str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2))
			+ 1);
	if (!joint_str)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		joint_str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
		joint_str[i++] = s2[j++];
	joint_str[i] = '\0';
	free(s1);
	return (joint_str);
}

static char	*ft_trim(char *stash)
{
	char	*ret;
	char	*temp;
	int		len;

	len = ft_strlen_param(stash, '\n');
	if (len != 0)
	{
		temp = ft_strchr(stash, '\n') + 1;
		ret = ft_strdup(temp);
	}
	else
		ret = NULL;
	free(stash);
	stash = NULL;
	return (ret);
}

static char	*ft_out(char *stash)
{
	int		i;
	int		j;
	int		len;
	char	*nl;

	i = -1;
	j = 0;
	while (stash[++i])
	{
		if (stash[i] == '\n' || stash[i + 1] == '\0')
		{
			len = i + 1;
			nl = ft_calloc((len + 1), sizeof(char));
			if (!nl)
				return (NULL);
			i = -1;
			while (++i < len)
				nl[i] = stash[i];
			nl[i] = '\0';
			return (nl);
		}
	}
	return (NULL);
}

static char	*ft_read(int fd, char *stash)
{
	char	*buf;
	int		read_bytes;

	read_bytes = 1;
	buf = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buf)
		return (NULL);
	while (read_bytes != 0 && ft_strchr(stash, '\n') == 0)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[read_bytes] = '\0';
		stash = ft_strjoin_gnl(stash, buf);
		if (!stash)
			return (NULL);
	}
	free(buf);
	return (stash);
}

char	*get_next_line(int fd)
{
	char		*ret;
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!stash)
	{
		stash = (char *)ft_calloc(1, 1);
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
	stash = ft_read(fd, stash);
	if (!stash)
		return (NULL);
	ret = ft_out(stash);
	stash = ft_trim(stash);
	return (ret);
}
