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


void minishell(char *line)
{
	ft_printf("You entered: %s\n", line);
}

int	readline_prompt(t_mini *mini)
{
	char	*line;
	char	buf[256];

	ascii_art_pattern();
	while (1)
	{
		if (getcwd(buf, sizeof(buf)) == NULL) // getcwd get the pwd show frond of the input
			error("Error: getcwd failed\n", 1);
		ft_printf("\033[32m\U0001F40C %s \033[31m>\033[0;39m", buf);
		if (!(line = readline(" ")))
			error("Error: readline failed\n", 1);
		if (ft_strncmp(line, "exit", 4) == 0)
		{
			free(line);
			break ;
		}
		//parsing using mini
		//
		//
		add_history(line);
		minishell(line);
		// clear_history();
		free(line);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_mini *mini;
	
	if (!(mini = malloc(sizeof(t_mini) * 1)))
		error("malloc fail.\n", 1);
	if (env_init(mini, env) != 1)
		error("fail to init env variables.", 3);
	readline_prompt(mini);
	return(0);
}
// create env linkedlist
int env_init(t_mini *mini, char **env)
{
	int i;
	char** env_split;
	t_env *env_content;
	t_list *node;

	i = 0;
	mini->env = NULL;
	while (env[i])
	{
		env_split = ft_split(env[i], '=');
		if (!env_split)
			error("malloc fail or null input?\n", 1);
		env_content = malloc(sizeof(t_env) * 1);
		if (!env_content)
			error("malloc fail.\n", 1);
		env_content->env_name = env_split[0]; //to be freed
		env_content->env_value = env_split[1]; // to be freed
		if (!mini->env)
		{
			mini->env = ft_lstnew(env_content);
			if (!mini->env)
				error("fail to init a node\n", 1);
		}
		else
		{
			node = ft_lstnew(env_content);
			if (!node)
				error("fail to init a node\n", 1);
			ft_lstadd_back(&mini->env, node);
		}
		//ft_printf("%s=%s\n", env_content->env_name, env_content->env_value);
		i++;
	}
	//ft_printf("\nbefore\n");
	//print_env(NULL);
	//char *str[1024] = {"KEY=12345", NULL};
	//export(str);
	//ft_printf("\nafter\n");
	//print_env(NULL);
	//char **str2 = ft_split("KEY=12345", '=');
	//ft_printf("\nafter unset\n");
	//unset(str2);
	//print_env(NULL);
	return (1);
}
