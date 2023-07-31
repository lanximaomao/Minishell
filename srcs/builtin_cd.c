/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:18:39 by lliu              #+#    #+#             */
/*   Updated: 2023/07/31 16:03:25 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

void	my_cd(char **arg, t_list **env)
{
	char	buf[1024];

	if (getcwd(buf, sizeof(buf)) != NULL)
		env_find_and_replace(env, "OLDPWD", buf, 1);
	if (arg[1] == NULL)
	{
		if (chdir(env_handler(env, "HOME")) != 0)
		{
			g_exitcode = 1;
			ft_putstr_fd(" Minishell: HOME not set\n", 2);
			return ;
		}
	}
	else if (chdir(arg[1]) != 0)
	{
		g_exitcode = 1;
		ft_putstr_fd(" No such file or directory\n", 2);
		return ;
	}
	if (getcwd(buf, sizeof(buf)) != NULL)
		env_find_and_replace(env, "PWD", buf, 1);
	g_exitcode = 0;
}
