#include "builtin.h"
#include "executor.h"

int	cmd_execution_in_child(t_token *token, t_mini *mini,
		char **env_exe)
{
	if (token->cmd == NULL)
		exit(g_exitcode);
	if (token->fd_in < 0 || token->fd_out < 0)
		exit(g_exitcode);
	dup2(token->fd_in, 0);
	close(token->fd_in);
	dup2(token->fd_out, 1);
	close(token->fd_out);
	if (run_builtin(token, &(mini->env)) == 1)
		exit(g_exitcode);
	if (contains_slash(token->cmd) == 0)
		cmd_with_no_path(token, mini, env_exe);
	else
		cmd_with_full_path(token, mini, env_exe);
	exit(g_exitcode);
}

void	cmd_with_no_path(t_token *token, t_mini *mini, char **env_exe)
{
	char	*tmp;
	char	*path_cmd;

	tmp = ft_strjoin("/", token->cmd);
	if (!tmp)
		ft_error(" fail in ft_strjoin\n", 1, 0);
	path_cmd = get_path_cmd(tmp, mini->env);
	free(tmp);
	if (!path_cmd)
		ft_error(" command not found", 127, 0);
	if (execve(path_cmd, token->args, env_exe) == -1)
	{
		if (errno == EACCES)
			ft_error(" Permission denied", 126, 0);
		else
			ft_error(" command not found", 127, 0);
	}
	free(path_cmd);
}

void	cmd_with_full_path(t_token *token, char **env_exe)
{
	struct stat	file_stat;

	if (access(token->cmd, F_OK) == 0)
	{
		if (access(token->cmd, X_OK) != 0)
			ft_error(" Permission denied", 126, 0);
		if (stat(token->cmd, &file_stat) == 0)
		{
			if (S_ISDIR(file_stat.st_mode))
				ft_error(" is a directory", 126, 0);
			else if (S_ISREG(file_stat.st_mode))
			{
				if (execve(token->cmd, token->args, env_exe) == -1)
					ft_error(" no such file or directory", 126, 0);
			}
		}
	}
	else
		ft_error(" No such file or directory", 127, 0);
}
