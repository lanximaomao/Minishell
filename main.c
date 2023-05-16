#include "minishell.h"
#include "builtin.h"
#include "signal.h"

int g_exitcode = 0;

int	readline_prompt(t_mini *mini)
{
	char	*line;
	char	buf[256];

	line = NULL;
	//ascii_art_pattern();
	while (1)
	{
		signal_main();
		if (!(line = readline("\033[32m\U0001F40C Minishell \033[31m$\033[0;39m ")))
		{
			g_exitcode = 0; // CTRL+D gives an EOF signal, and sets line to NULL.
			printf("exit\n");
			exit(g_exitcode);
		}

			//ft_error("Readline error", FUNC);
		//if (!ft_strncmp(line, "exit", 5))
		//{
		//	free(line);
		//	break ;
		//}
		//parsing using mini
		add_history(line);
		// execute all the input cmd, while loop for signal processing
		minishell(mini, line, 0); // exitcode is 0, handle in later
	}
	clear_history(); // ! why rl_clear_history does not work?
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_mini *mini;


	if (argc != 1 || argv[1])
		ft_error("Wrong input!", FUNC);
	mini = malloc(sizeof(t_mini) * 1);
	if (!mini)
		ft_error("malloc fail.\n", 1);
	if (env_init(mini, env) != 1)
		ft_error("fail to init env variables.", 3);
	readline_prompt(mini);
	return(0);
}

void ascii_art_pattern()
{
	printf("\n\n/* ************************************************************************** */");
	printf("\n/*                                                                            */");
	printf("\n/*                                                        :::      ::::::::   */");
	printf("\n/*   MINISHELL                                          :+:      :+:    :+:   */");
	printf("\n/*                                                    +:+ +:+         +:+     */");
	printf("\n/*   Version: 0.0.1                                 +#+  +:+       +#+        */");
	printf("\n/*                                                +#+#+#+#+#+   +#+           */");
	printf("\n/*   Created: 2023/03/16                               #+#    #+#             */");
	printf("\n/*   Updated: 2023/03/16                              ###   ########.fr       */");
	printf("\n/*                                                                            */");
	printf("\n/* ************************************************************************** */\n\n");
}

/*
\U0001F600 for smily face
\U0001F333 for a tree
\U0001F41A for a shell
\U0001F40C for a snail
*/

// process_signal controls

