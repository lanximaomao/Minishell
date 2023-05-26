#include "builtin.h"
#include "executor.h"
#include "signal.h"

/* return values to be fixed */
int	executor(t_mini *mini, int size)
{
	int	*pid;
	int	*status;

	pid = malloc(sizeof(int) * size);
	if (!pid)
		ft_error(" pid malloc fail", 1);
	status = malloc(sizeof(int) * size);
	if (!status)
		ft_error("status malloc fail", 1);
	loop(mini, size, pid, status);
	get_exitcode(size, pid, status);
	return (0);
}

void	loop(t_mini *mini, int size, int *pid, int *status)
{
	int		i;
	t_list	*tmp;
	t_token	*token;
	int		fd_pipe[2];

	i = -1;
	tmp = mini->cmd_lst;
	while (tmp && ++i < size)
	{
		token = (t_token *)tmp->content;
		if (handle_io(token, i, size, fd_pipe) != -1 && size == 1
			&& buildtin_or_not(token, mini->env) > 0 && single_builtin(token,
				mini->env) == 0)
			return ;
		pid[i] = fork();
		if (pid[i] == -1)
			ft_error(" fork failed", 4);
		else if (pid[i] == 0)
		{
			if (i < size - 1)
				close(fd_pipe[0]);
			cmd_execution_in_children(token, size, mini);
		}
		close(token->fd_in);
		close(token->fd_out);
		//close(fd_pipe[0]);
		//close(fd_pipe[1]);
		tmp = tmp->next;
	}
}

int	single_builtin(t_token *token, t_list *env)
{
	int	in;
	int	out;

	in = dup(0);
	out = dup(1);
	dup2(token->fd_in, 0);
	close(token->fd_in);
	dup2(token->fd_out, 1);
	close(token->fd_out);
	buildtin_run(token, &env);
	dup2(in, 0);
	close(in);
	dup2(out, 1);
	close(out);
	return (0);
}

/*
** printf("cmd_order=%d, fd_in=%d, fd_out=%d, pipe[0]=%d, pipe[1]=%d\n",
** cmd_order, token->fd_in, token->fd_out, fd_pipe[0], fd_pipe[1]);
*/
int	handle_io(t_token *token, int cmd_order, int size, int *fd_pipe)
{
	int	in;
	int	out;

	if (size == 1)
	{
		token->fd_in = dup(0);
		token->fd_out = dup(1);
		return (get_file_fd(token));
	}
	if (cmd_order != 0)
		token->fd_in = fd_pipe[0];
	if (cmd_order != size - 1 && pipe(fd_pipe) == -1)
		ft_error("error in creating pipes.\n", 4);
	if (cmd_order == 0)
	{
		token->fd_in = dup(0);
		token->fd_out = fd_pipe[1];
	}
	else if (cmd_order != 0 && cmd_order != size - 1)
		token->fd_out = fd_pipe[1];
	else
		token->fd_out = dup(1);
	return (get_file_fd(token));
}

/*
** -1 means problem occured with infile
** -2 means problem occured with outfile
*/
int	get_file_fd(t_token *token)
{
	int	i;

	i = 0;
	if (get_infile_fd(token) == -1)
		return (-1);
	while (i < token->num_outfile_type)
	{
		if (token->output_type[i] == 2)
			token->fd_out = open(token->outfile[i],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			token->fd_out = open(token->outfile[i],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (token->fd_out == -1)
		{
			perror("fail to create or open outfile");
			g_exitcode = 1;
			return (-2);
		}
		if (i + 1 < token->num_outfile_type)
			close(token->fd_out);
		i++;
	}
	return (0);
}

int	get_infile_fd(t_token *token)
{
	int	i;

	i = 0;
	while (i < token->num_infile)
	{
		token->fd_in = open(token->infile[i], O_RDONLY);
		if (token->fd_in == -1)
		{
			perror("minishell: infile");
			g_exitcode = 1;
			return (1);
		}
		if (i + 1 < token->num_infile)
			close(token->fd_in);
		i++;
	}
	return (0);
}

int	cmd_execution_in_children(t_token *token, int size, t_mini *mini)
{
	char	*tmp;
	char	*path_cmd;

	child_error_handle(token, mini);
	if (access(token->cmd, X_OK) == 0)
	{
		if (execve(token->cmd, token->args, env_convert(mini->env)) == -1)
		{
			g_exitcode = 126;
			ft_error(" no such file or directory", g_exitcode);
		}
	}
	else
	{
		tmp = ft_strjoin("/", token->cmd);
		path_cmd = get_path_cmd(tmp, mini->env);
		free(tmp);
		if (!path_cmd || execve(path_cmd, token->args,
				env_convert(mini->env)) == -1)
		{
			g_exitcode = 127;
			ft_error(" command not found", g_exitcode);
		}
	}
	exit(g_exitcode);
}

void	child_error_handle(t_token *token, t_mini *mini)
{
	if (token->cmd == NULL)
		exit(g_exitcode);
	if (token->fd_in < 0 || token->fd_out < 0)
		exit(g_exitcode);
	dup2(token->fd_in, 0);
	close(token->fd_in);
	dup2(token->fd_out, 1);
	close(token->fd_out);
	if (buildtin_run(token, &(mini->env)) == 1)
		exit(g_exitcode);
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
			ft_error(" string join failed. \n", 1);
		if (access(path_cmd, X_OK) == 0)
			break ;
		if (path_cmd)
		{
			free(path_cmd);
			path_cmd = NULL;
		}
		i++;
	}
	return (path_cmd);
}

char	**get_path_env(t_list *env)
{
	int		i;
	t_list	*tmp;
	char	**env_content;
	char	**path_env;

	i = 0;
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
		ft_error(" malloc fail or PATH is NULL.\n", 1);
	return (path_env);
}

void	get_exitcode(int size, int *pid, int *status)
{
	int	i;

	i = 0;
	while (i < size)
	{
		waitpid(pid[i], &status[i], 0);
		i++;
	}
	if (g_exitcode != -1 && WIFEXITED(status[size - 1]))
		g_exitcode = WEXITSTATUS(status[size - 1]);
}
