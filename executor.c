#include "minishell.h"
#include "buidin.h"
#include "executor.h"

int executor(t_mini *mini)
{
	int i;
	int *pid;
	int *status;
	int size;
	int fd_pipe[2];
	t_list *tmp;

	i = 0;
	size = ft_lstsize(mini->cmd_lst);
	if (size == 0)
		return(0);

	if (size == 1)
	{
		cmd_single(mini);
		return (0);
	}
	pid = malloc(sizeof(int) * size);
	if (!pid)
		ft_error("pid malloc fail", 1);
	// why would I need status?
	status = malloc(sizeof(int) * size);
	if (!status)
		ft_error("status malloc fail", 1);
	//init fd for creating pipes

	ft_printf("size = %d\n", size);

	fd_pipe = (int**)malloc(sizeof(int*) * (size - 1));
	if (!fd_pipe)
		ft_error("fd_pipe malloc fail", 1);
	while (i < size - 1)
	{
		fd_pipe[i] = malloc(sizeof(int) * 2);
		if (!fd_pipe[i])
			ft_error("malloc fail", 1);
		i++;
	}
	//create (size - 1) pipes
	handel_pipe_create(fd_pipe, size);
	tmp = mini->cmd_lst;
	i = 0;
	while (tmp && i < size)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			ft_error("fork failed", 4);
		else if (pid[i] == 0)
			cmd_pipe(mini, fd_pipe, size, i);
		tmp = tmp->next;
		i++;
	}
	i = 0;
	while(i++ < size)
		waitpid(pid[i], &status[i], 0);

	//ft_printf("hello from minishell.\n");
	return(status[i]);
}

// handel files !!
int cmd_single(t_mini *mini)
{
	int pid;
	char* path_cmd;
	char* tmp;
	int status;
	t_token *token;

	token = (t_token*)(mini->cmd_lst->content);

	pid=fork();
	if (pid == -1)
		ft_error("fork failed.\n", 4);
	else if (pid == 0)
	{
		if (handel_file_single(token) == 1)
			exit(1);
		if (access(token->cmd, X_OK) == 0)
			execve(token->cmd, token->args, env_convert(mini->env));
		else
		{
			tmp = ft_strjoin("/", token->cmd);//to be freed
			path_cmd = get_path_cmd(tmp, mini->env);
			free(tmp);
			execve(path_cmd, token->args, env_convert(mini->env));
		}
	}
	waitpid(pid, &status, 0);
	return(0);
}

int cmd_pipe(t_mini *mini, int** fd_pipe, int size, int which_pipe)
{
	t_token* token;
	char* tmp;
	char* path_cmd;

	token = (t_token*)mini->cmd_lst->content;
	// close unused pipes
	handel_pipe_close(fd_pipe, size, which_pipe);
	//handel input and output
	handel_file(token, fd_pipe, size, which_pipe);
	// handel in and out
	dup2(token->fd_in, 0);
	dup2(token->fd_out, 1);
	//close other fd, should I close fd_in when it is 0 and fd_out when it is 1???
	if (close(token->fd_in) == -1 || close(token->fd_out) == -1)
		ft_error("file cannot be closed.\n", 4);
	if (close(fd_pipe[which_pipe][0]) == -1 || close(fd_pipe[which_pipe][1]) == -1)
		ft_error("file cannot be closed.\n", 4);

	// check if it is a buildin function, if yes, run and return.
	if (is_buildin(mini->cmd_lst, mini->env) == 1)
		return (0);
	// not a buildin, check if full path the already available, if yes, run and return.
	if (access(token->args[0], X_OK) == 0)
	{
		if (execve(token->args[0], token->args, env_convert(mini->env)) == -1)
			ft_error("Cannot execute command.\n", 4);
	}
	else
	{
		tmp = ft_strjoin("/", token->args[0]);//to be freed
		path_cmd = get_path_cmd(tmp, mini->env);
		free(tmp);
		if (execve(path_cmd, token->args, env_convert(mini->env)) == -1)
			ft_error("Cannot execute command.\n", 4); // !error return
	}
	return(1);
}


// loop through number of files

int handel_file_single(t_token* token)
{
	int i;

	i = 0;

	if (token->num_infile == 0)
		token->fd_in = 0;

	while ( i < token->num_infile)
	{
		token->fd_in = open(token->infile[i], O_RDONLY);
		if (token->fd_in == -1)
		{
			ft_printf("Fail to open infile.\n");
			return (1);
		}
		if (i + 1 < token->num_infile)
			close(token->fd_in);
		i++;
	}
	i = 0;
	if (token->num_outfile_type == 0)
		token->fd_out = 1;
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


/* in order to save the fd_in and fd_out, add definition at s_token struct*/
// should use dup2 instead of open and close!!
int handel_file(t_token* token, int** fd_pipe, int which_pipe, int size)
{
	int i;

	i = 0;
	// loop through each infile
	ft_printf("handel files %s.\n", token->infile[0]);
	while ( i < token->num_infile)
	{
		token->fd_in = open(token->infile[i], O_RDONLY);
		if (token->fd_in == -1)
		{
			ft_printf("Fail to open infile.\n");
			return (1);
		}
		if (i + 1 < token->num_infile)
			close(token->fd_in);
		i++;
	}
	// if no infile is given,
	// by default it should take stdin if it is the first cmd
	// or reading from the connected pipes
	if (token->num_infile == 0) // or token->infile == NULL?
	{
		if (which_pipe == 0)
			token->fd_in = 0;
		else
			token->fd_in = fd_pipe[which_pipe][0];
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


	// if no outfile is given,
	// by default it should be stdout if it's the last cmd
	// otherwise, it should redirect to the connected pipe
	if (token->num_outfile_type == 0) // or token->outfile == NULL?
	{
		if (which_pipe == size - 1 - 1)
			token->fd_out = 1;
		else
			token->fd_out = fd_pipe[which_pipe][1];
	}
	return(0);
}

void handel_pipe_create(int** fd_pipe, int size)
{
	int i;

	ft_printf("creating %d pipes.\n", size - 1);
	//set up pipe
	i = 0;
	while (i < size - 1)
	{
		if (pipe(fd_pipe[i]) == -1)
			ft_error("error in creating pipes.\n", 4);
		i++;
	}
}

// this will be used in each children processor to close all the irrelevant pipes.
int handel_pipe_close(int **fd_pipe, int size, int which_pipe)
{
	// for pipe[i], what should I close?
	int i;

	i = 0;
	while ( i < size - 1)
	{
		if ( i != which_pipe)
		{
			if (fd_pipe[i][0] > 0 && close(fd_pipe[i][0]) == -1)
				ft_error("file cannot be closed.", 4);
			if (fd_pipe[i][1] > 0 && close(fd_pipe[i][1]) == -1)
				ft_error("file cannot be closed.", 4);
		}
		i++;
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


