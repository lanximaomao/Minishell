#include "buidin.h"
#include "executor.h"


int executor_single(t_mini *mini)
{
	int pid;
	int status;
	t_token* token;

	token = (t_token*)mini->cmd_lst->content;
	if (handel_file(token))
		return(1);
	pid = fork();
	if (pid == -1)
		ft_error("fork failed", 4);
	else if (pid == 0)
		cmd_execution_in_children_one(token, 1, mini);
	close(token->fd_in);
	close(token->fd_out);
	waitpid(pid, &status, 0);
	return(status);
}

int executor(t_mini *mini, int size)
{
	int i;
	int *pid;
	int *status;
	int fd_pipe[2];
	t_list *tmp;
	t_token* token;

	i = 0;
	tmp = mini->cmd_lst;

	pid = malloc(sizeof(int) * size);
	if (!pid)
		ft_error("pid malloc fail", 1);
	status = malloc(sizeof(int) * size);
	if (!status)
		ft_error("status malloc fail", 1);
	while (tmp && i < size)
	{
		token = (t_token*) tmp->content;
		if (handel_io(token, fd_pipe, i, size) == 1)
			return(1);
		pid[i] = fork();
		if (pid[i] == -1)
			ft_error("fork failed", 4);
		else if (pid[i] == 0)
			cmd_execution_in_children_more(token, fd_pipe, size, mini);
		close(token->fd_in);
		close(token->fd_out);
		tmp = tmp->next;
		i++;
	}
	i = 0;
	while(i < size)
	{
		waitpid(pid[i], &status[i], 0);
		i++;
	}
	return(status[i]);
}

///* still happening in main processor*/
int handel_io(t_token* token, int* fd_pipe, int cmd_order, int size)
{
	//printf("before %d, fd_in = %d, fd_out = %d\n", cmd_order, token->fd_in, token->fd_out);
	// no need to create any pipe while reaching the last cmd
	//if (cmd_order != 0 && size > 1)
	//	token->fd_in = fd_pipe[0];
	if (cmd_order != 0)
	{
		dup2(fd_pipe[0], token->fd_in);
		close(fd_pipe[0]);
		close(fd_pipe[1]);
	}
	if (cmd_order != size - 1 && pipe(fd_pipe) == -1)//
		ft_error("error in creating pipes.\n", 4);
	// io from pipe
	if (cmd_order == 0) // first cmd
	{
		token->fd_in = dup(0);
		token->fd_out = fd_pipe[1];
	}
	else if (cmd_order == size - 1) // last cmd, token->fd_in shoud be from a previous comd output
		token->fd_out = dup(1);//no need
	else if (cmd_order > 0 && cmd_order < size - 1) // middle cmd, token->fd_in shoud be from a previous comd output
		token->fd_out = fd_pipe[1];

	//printf("after %d, fd_in = %d, fd_out = %d\n", cmd_order, token->fd_in, token->fd_out);
	if (handel_file(token) == 1)
		return (1);
	return (0);
}

// loop through number of files
int handel_file(t_token* token)
{
	int i;

	i = 0;
	while ( i < token->num_infile)
	{
		token->fd_in = open(token->infile[i], O_RDONLY);
		if (token->fd_in == -1)
		{
			perror("minishell: infile");
			return(1);
		}

		if (i + 1 < token->num_infile)
			close(token->fd_in);
		i++;
	}
	i = 0;
	while (i < token->num_outfile_type)
	{
		if (token->output_type[i] == 2) // append mode
			token->fd_out = open(token->outfile[i], O_WRONLY | O_CREAT|O_APPEND, 0644);
		else
			token->fd_out = open(token->outfile[i], O_WRONLY | O_CREAT|O_TRUNC, 0644);
		if (token->fd_out == -1)
		{
			perror("Fail to create or open outfile");//exit or not?
			return(2);
		}
		if (i + 1 < token->num_outfile_type)
			close(token->fd_out);
		i++;
	}
	return(0);
}

int cmd_execution_in_children_one(t_token* token, int size, t_mini *mini)
{
	char* tmp;
	char* path_cmd;

	dup2(token->fd_in, 0);
	close(token->fd_in);
	dup2(token->fd_out, 1);
	close(token->fd_out);
	if (is_buildin(token, mini->env) == 1)
		return (0);
	if (access(token->cmd, X_OK) == 0)
	{
		if (execve(token->cmd, token->args, env_convert(mini->env)) == -1)
			ft_error("Cannot execute command", 4); // !error return
	}
	else
	{
		tmp = ft_strjoin("/", token->cmd);//to be freed
		path_cmd = get_path_cmd(tmp, mini->env);
		free(tmp);
		if (execve(path_cmd, token->args, env_convert(mini->env)) == -1)
			ft_error("Cannot execute command", 4); // !error return
	}
	return(1);
}

int cmd_execution_in_children_more(t_token* token, int* fd_pipe, int size, t_mini *mini)
{
	cmd_execution_in_children_one(token, size, mini);
	close(fd_pipe[1]);
	return(1);
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


