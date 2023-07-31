/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:18:59 by lliu              #+#    #+#             */
/*   Updated: 2023/07/31 16:03:34 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

/* env with no options or aguments */
int	my_env(t_list *env)
{
	t_list	*tmp;
	char	**env_content;

	tmp = env;
	while (tmp)
	{
		env_content = (char **)tmp->content;
		if (ft_strncmp(env_content[1], "", 1))
			printf("%s=%s\n", env_content[0], env_content[1]);
		tmp = tmp->next;
	}
	g_exitcode = 0;
	return (0);
}
