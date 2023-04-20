/*
allowed function:
readline, rl_clear_history, rl_on_new_line,
rl_replace_line, rl_redisplay, add_history,
printf, malloc, free, write, access, open, read,
close, fork, wait, waitpid, wait3, wait4, signal,
sigaction, sigemptyset, sigaddset, kill, exit,
getcwd, chdir, stat, lstat, fstat, unlink, execve,
dup, dup2, pipe, opendir, readdir, closedir,
strerror, perror, isatty, ttyname, ttyslot, ioctl,
getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
tgetnum, tgetstr, tgoto, tputs

possible work distribution:
1. parsing
2. argument checking
3. execution
4. redirection
5. piping
6. environment variables
7. build-in functions
8. signal handling

build-in functions:
echo, pwd, cd, env, export, unset, exit
*/

/*  gcc minishell.c -lreadline */
#include "minishell.h"
#include "buidin.h"
#include "pipe.h"

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

// build-ins
// pipes

void minishell(t_mini *mini, char *line)
{
	int pid1;
	int status;
	char** cmd_args;
	t_list *line_lst = NULL;
	t_list *cmd_lst = NULL;


	// check for single buildin call
	if (*line == '\0')
		return;
	cmd_args = ft_split(line, ' ');
	if (!cmd_args)
		ft_error("split function returns null.\n", 1);



	if (is_buildin(cmd_args, mini->env) == 1)
		return;
	// if not a buildin, start to fork....
	pid1 = fork();
	if (pid1 == -1)
		ft_error("fork failed.\n", 1);
	else if (pid1 == 0)
		cmd(mini, line); //children process
	waitpid(pid1, &status, 0);
	//save the exit status to env variable, but how about for buildins?
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
