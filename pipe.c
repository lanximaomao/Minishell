#include "pipe.h"
#include "buidin.h"
#include "minishell.h"

int cmd(char* line)
{
	char** cmd_args;
	char* path_cmd;
	char* tmp;

	cmd_args = ft_split(line, ' ');
	if (!cmd_args)
		error("split function returns null.\n", 1);
	if (access(cmd_args[0], X_OK) == 0)
		execve(cmd_args[0], cmd_args, update_env());
	else
	{
		tmp = ft_strjoin("/", cmd_args[0]);//to be freed
		path_cmd = get_path_cmd(tmp);
		free(tmp);
		execve(path_cmd, cmd_args, update_env());
	}
	return(0);
}

char* get_path_cmd(char* str)
{
	int i;
	char **path_env;
	char *path_cmd;

	i = 0;
	path_env = get_path_env();
	while (path_env[i])
	{
		path_cmd = ft_strjoin(path_env[i], str);
		if (!path_cmd)
			error("string join failed. \n", 1);
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

char **get_path_env()
{
	int i;
	t_list	*tmp;
	t_env*	env_content;
	char **path_env;

	i = 0;
	tmp = mini->env;
	while (tmp)
	{
		env_content = (t_env*)tmp->content;
		if (ft_strncmp(env_content->env_name, "PATH", 4) == 0)
			break;
		else
			tmp = tmp->next;
	}
	path_env = ft_split(env_content->env_value, ':');
	if (!path_env)
		error("Malloc fail or PATH is NULL.\n", 1);
	return(path_env);
}

char** update_env()
{
	int i;
	int size;
	char** ret;
	char* ret_tmp1;
	char* ret_tmp2;
	t_list *tmp;
	t_env *env_content;

	i = 0;
	size = 0;
	tmp = mini->env;
	size = ft_lstsize(mini->env);
	ret = (char**)malloc(sizeof(char*) * (size + 1)); // to be freed
	if (!ret)
		error("malloc fail.\n", 1);
	ret[size] = NULL;
	while (i <  size)
	{
		env_content = (t_env *)tmp->content;
		ret_tmp1 = ft_strjoin(env_content->env_name, "=");
		ret_tmp2 = ft_strjoin(env_content->env_value, "\n");
		ret[i] = ft_strjoin(ret_tmp1, ret_tmp2); // to be freed
		free(ret_tmp1);
		free(ret_tmp2);
		tmp = tmp->next;
		i++;
	}
	return(ret);
}


