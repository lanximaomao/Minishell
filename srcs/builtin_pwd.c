/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:19:21 by lliu              #+#    #+#             */
/*   Updated: 2023/07/31 16:03:41 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

/* pwd with no options */
void	my_pwd(void)
{
	char	buf[1024];

	if (getcwd(buf, sizeof(buf)) != NULL)
		ft_printf("%s\n", buf);
	g_exitcode = 0;
}
