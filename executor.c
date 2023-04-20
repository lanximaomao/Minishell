#include "pipe.h"
#include "buidin.h"
#include "minishell.h"


void minishell(t_mini *mini, char *line)
{
	if (*line == '\0')
		return;
	//lexer parser and expander, and heredoc is also handelled here
	//check for parsing error
	// check for single buildin, if yes, just function call and return
	if (ft_lstsize(t_mini->cmd_lst) == 1 && is_buildin(cmd_args, mini->env) == 1)
		return;

	// if not a buildin or there is more than one buidin, start to fork....
	run_run_run(mini);
}

int run_run_run(t_mini *mini)
{
	int i;
	int *pid;
	int *status;
	int size;

	i = 0;
	size = ft_lstsize(mini->cmd_lst);
	pid = malloc(sizeof(int) * size);
	if (!pid)
		ft_error("malloc fail.\n", 1);
	status = malloc(sizeof(int) * size);
	if (!status)
		ft_error("malloc fail.\n", 1);
	tmp = mini->cmd_lst;
	while (mini->cmd_lst)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			ft_error("fork failed.\n", 4);
		else if (pid[i] == 0)
			cmd(mini->cmd_lst, line); //node
		tmp = tmp->next;
	}
	i = 0;
	while(i++ < size)
		waitpid(pid1, &status[i], 0);
}

int cmd(t_mini *mini, char* line)
{
	t_token *token;

	token = (t_token*)(mini->cmd_lst);

	//handel input and output
	handel_file(mini->cmd_lst);

	// check if it is a buildin function, if yes, run and return.
	if (is_buildin(token->args, mini->env) == 1)
		return;
	// not a buildin, check if full path the already available, if yes, run and return.
	if (access(token->args[0], X_OK) == 0)
		execve(token->args[0], token->args, env_convert(mini->env));
	else
	{
		tmp = ft_strjoin("/", token->args[0]);//to be freed
		path_cmd = get_path_cmd(tmp, mini->env);
		free(tmp);
		execve(path_cmd, cmd_args, env_convert(mini->env)); // !error return
	}
	return(0);
}

/* in order to save the fd_in and fd_out, add definition at s_token struct*/
int handel_file(t_list *cmd_lst)
{
	t_token *token;
	int i;

	i = 0;
	token = (t_token *)cmd_lst->content;
	// loop through each infile
	while (token->infile[i])
	{
		token->fd_in = open(token->infile[i], O_RDONLY);
		if (token->fd_in == -1)
		{
			perror("Fail to open infile"); // cannot exit, so that next file could be able to checked out.
			return (1);
		}
		if (token->infile[i + 1] != NULL)
			close(token->fd_in);
		i++;
	}
	// if no infile is given, by default it should take stdin
	if (token->infile[0] == NULL)
		token->fd_in = 0;
	//loop through each outfile
	i = 0;
	while (token->outfile[i])
	{
		token->fd_out = open(token->outfile[i], O_WRONLY | O_CREAT|O_TRUNC, 0644);
		if (token->fd_out == -1)
		{
			perror("Fail to create or open outfile");//exit or not?
			return(2);
		}
		if (token->outfile[i + 1] != NULL)
			close(token->fd_out);
		i++;
	}
	// if no outfile is given, by default it should be stdout
	if (token->outfile[0])
		token->fd_out = 1;
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


