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

	ascii_art_pattern();
	while (1)
	{
		line = readline("\033[32m\U0001F40C Minishell > ");
		if (!line)
		{
			ft_printf("\n");
			break ;
		}
		if (ft_strncmp(line, "exit", 4) == 0)
		{
			free(line);
			break ;
		}
		//parsing using mini
		add_history(line);
		minishell(line);
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
		error("malloc fail.\n", 1);
	if (env_init(mini, env) != 1)
		error("fail to init env variables.", 3);
	readline_prompt(mini);
	return(0);
}

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
		env_content->env_name = ft_strdup(env_split[0]); //free
		env_content->env_value = ft_strdup(env_split[1]); // free
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
		free(env_split[0]);
		free(env_split[1]);
		free(env_split);
		i++;
	}
	return (1);
}
