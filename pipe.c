#include "pipe.h"
#include "buidin.h"
#include "minishell.h"

int cmd(t_mini *mini, char* line)
{
	char** cmd_args;
	char* path_cmd;
	char* tmp;

	if (*line == '\0')
		return(1);
	cmd_args = ft_split(line, ' ');
	if (!cmd_args)
		ft_error("split function returns null.\n", 1);
	if (access(cmd_args[0], X_OK) == 0)
		execve(cmd_args[0], cmd_args, env_convert(mini->env));
	else
	{
		tmp = ft_strjoin("/", cmd_args[0]);//to be freed
		path_cmd = get_path_cmd(tmp, mini->env);
		free(tmp);
		execve(path_cmd, cmd_args, env_convert(mini->env));
	}
	return(0);
}

char* get_path_cmd(char* str, t_list *env)
{
	int i;
	char **path_env;
	char *path_cmd;

	i = 0;
	path_env = get_path_env(env);
	while (path_env[i])
	{
		path_cmd = ft_strjoin(path_env[i], str);
		if (!path_cmd)
			ft_error("string join failed. \n", 1);
		if (access(path_cmd, X_OK) == 0)
			break;
		if (path_cmd)
		{
			free(path_cmd);
			path_cmd = NULL;
		}
		i++;
	}
	return(path_cmd);
}

char **get_path_env(t_list *env)
{
	int i;
	t_list	*tmp;
	char**	env_content;
	char **path_env;

	i = 0;
	tmp = env;
	while (tmp)
	{
		env_content = (char**)tmp->content;
		if (ft_strncmp(env_content[0], "PATH", 4) == 0)
			break;
		else
			tmp = tmp->next;
	}
	path_env = ft_split(env_content[1], ':');
	if (!path_env)
		ft_error("Malloc fail or PATH is NULL.\n", 1);
	return(path_env);
}


