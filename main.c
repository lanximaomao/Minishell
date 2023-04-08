/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linlinsun <linlinsun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:56:42 by linlinsun         #+#    #+#             */
/*   Updated: 2023/04/08 11:24:21 by linlinsun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_mini *mini;
	int ret;

	mini = malloc(sizeof(t_mini) * 1);
	if (!mini)
		error("malloc fail.\n", 1);
	ret = mini_init(mini);
	printf("%s\n", getenv("PATH"));
	printf("\n\n%s\n", env[0]);
	printf("\n\n%s\n", env[1]);
	printf("\n\n%s\n", env[2]);
	return(0);
}

int mini_init(t_mini *mini)
{
	mini->env = malloc(sizeof(t_env)*1);
	mini->input = malloc(sizeof(t_input) * 1);
	if (!mini->env || !mini->input)
		error("malloc fail.\n", 1);
	return (1); // true
}

