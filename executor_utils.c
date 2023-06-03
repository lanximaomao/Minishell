#include "builtin.h"
#include "executor.h"

int	create_child(int *pid, int i)
{
	pid[i] = fork();
	if (pid[i] == -1)
		ft_error(" fork failed", 4, 0);
	return (pid[i]);
}

int	contains_slash(const char *str)
{
	while ((*str))
	{
		if (*str == '/')
			return (1);
		str++;
	}
	return (0);
}

void	free_and_close(char **env_exe, int fd_in, int fd_out)
{
	free_char(env_exe);
	close(fd_in);
	close(fd_out);
}

char	*get_path_cmd(char *str, t_list *env)
{
	int		i;
	char	**path_env;
	char	*path_cmd;

	i = 0;
	path_env = get_path_env(env);
	while (path_env[i])
	{
		path_cmd = ft_strjoin(path_env[i], str);
		if (!path_cmd)
			ft_error(" string join failed. \n", 1, 0);
		if (access(path_cmd, X_OK) == 0)
			break ;
		if (path_cmd)
		{
			free(path_cmd);
			path_cmd = NULL;
		}
		i++;
	}
	free_char(path_env);
	return (path_cmd);
}

char	**get_path_env(t_list *env)
{
	t_list	*tmp;
	char	**env_content;
	char	**path_env;

	tmp = env;
	while (tmp)
	{
		env_content = (char **)tmp->content;
		if (ft_strncmp(env_content[0], "PATH", 4) == 0)
			break ;
		else
			tmp = tmp->next;
	}
	path_env = ft_split(env_content[1], ':');
	if (!path_env)
		ft_error(" malloc fail or PATH is NULL.\n", 1, 0);
	return (path_env);
}
