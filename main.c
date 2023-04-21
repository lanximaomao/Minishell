#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_mini *mini;

	mini = malloc(sizeof(t_mini) * 1);
	if (!mini)
		ft_error("malloc fail.\n", 1);
	if (env_init(mini, env) != 1)
		ft_error("fail to init env variables.", 3);
	readline_prompt(mini);
	return(0);
}

int	readline_prompt(t_mini *mini)
{
	char	*line;
	char	buf[256];

	//ascii_art_pattern();
	while (1)
	{
		if (getcwd(buf, sizeof(buf)) == NULL) // getcwd get the pwd show frond of the input
			ft_error("Error: getcwd failed\n", 1);
		line = readline("\033[32m\U0001F40C Minishell > ");
		if (!line)
		{
			ft_printf("\n");
			break ;
		}
		if (ft_strncmp(line, "exit", ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		//parsing using mini
		add_history(line);
		minishell(mini, line);
		free(line);
	}
	clear_history(); // ! why rl_clear_history does not work?
	return (0);
}

void ascii_art_pattern()
{
	ft_printf("\n\n/* ************************************************************************** */");
	ft_printf("\n/*                                                                            */");
	ft_printf("\n/*                                                        :::      ::::::::   */");
	ft_printf("\n/*   MINISHELL                                          :+:      :+:    :+:   */");
	ft_printf("\n/*                                                    +:+ +:+         +:+     */");
	ft_printf("\n/*   Version: 0.0.1                                 +#+  +:+       +#+        */");
	ft_printf("\n/*                                                +#+#+#+#+#+   +#+           */");
	ft_printf("\n/*   Created: 2023/03/16                               #+#    #+#             */");
	ft_printf("\n/*   Updated: 2023/03/16                              ###   ########.fr       */");
	ft_printf("\n/*                                                                            */");
	ft_printf("\n/* ************************************************************************** */\n\n");
}

/*
\U0001F600 for smily face
\U0001F333 for a tree
\U0001F41A for a shell
\U0001F40C for a snail
*/
