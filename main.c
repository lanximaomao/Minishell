#include "minishell.h"
#include "buidin.h"



int	readline_prompt(t_mini *mini)
{
	char	*line;
	char	buf[256];

	line = NULL;
	//ascii_art_pattern();
	while (1)
	{
		//if (!getcwd(buf, sizeof(buf))) // getcwd get the pwd show frond of the input
		//	ft_error("Getcwd error", FUNC);
		//printf("\033[0;94m%s\033[0;39m\n", buf);
		if (!(line = readline("\033[32m\U0001F40C Minishell \033[31m$\033[0;39m ")))
			ft_error("231Readline error", FUNC);
		if (!ft_strncmp(line, "exit", 5))
		{
			free(line);
			break ;
		}
		//parsing using mini
		add_history(line);
		// execute all the input cmd, while loop for signal processing
		minishell(mini, line, 0); // exitcode is 0, handle in later


	}
	clear_history(); // ! why rl_clear_history does not work?
	return (0);
}

/* ctrl + \ = SIGQUIT, does nothing */
//! by two times ctrl + \ we got an readline error
void sa_handel_sigquit(int sig)
{
	printf("I am calling CTRL + \\");
	//fflush(stdout);
	return;
}

/* ctrl + D = EOF, exits the shell */
// ! Readline error: interrupted system call.
void sa_handel_sigeof(int sig)
{
	printf("I am calling CTRL + D");
	//fflush(stdout);
	return;
}

/* ctrl + c should dispays a new prompt on a new line */
//! by two times ctrl + c we got an readline error
void sa_handel_sigint(int sig)
{
	int fd;
	dup2(fd, 0);
	printf("\n");
	//printf("\033[32m\U0001F40C Minishell \033[31m$\033[0;39m ");
	return;
}

int	main(int argc, char **argv, char **env)
{
	t_mini *mini;

	struct sigaction sa_int; //ctrl + c
	struct sigaction sa_eof; //ctrl + d
	struct sigaction sa_quit; //ctrl + \

	sa_int.sa_handler = &sa_handel_sigint;
	sa_eof.sa_handler = &sa_handel_sigeof;
	sa_quit.sa_handler = &sa_handel_sigquit;
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGUSR1, &sa_eof, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);

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

