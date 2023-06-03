#include "builtin.h"

/*
** if no cmd is given, just return.
** this is to avoide the segfault by doing << f1
*/
int	is_builtin(t_token *token)
{
	int	len;

	if (token->cmd == NULL)
		return (-1);
	len = ft_strlen(token->cmd);
	if (len == 2 && ft_strncmp(token->cmd, "cd", len) == 0)
		return (1);
	else if (len == 3 && ft_strncmp(token->cmd, "pwd", len) == 0)
		return (2);
	else if (len == 3 && ft_strncmp(token->cmd, "env", len) == 0)
		return (3);
	else if (len == 4 && ft_strncmp(token->cmd, "exit", len) == 0)
		return (4);
	else if (len == 4 && ft_strncmp(token->cmd, "echo", len) == 0)
		return (5);
	else if (len == 5 && ft_strncmp(token->cmd, "unset", len) == 0)
		return (6);
	else if (len == 6 && ft_strncmp(token->cmd, "export", len) == 0)
		return (7);
	return (0);
}

int	run_builtin(t_token *token, t_list **env)
{
	int	ret;

	ret = is_builtin(token);
	if (token->fd_in < 0 || token->fd_out < 0)
		return (-1);
	if (ret == 0)
		return (0);
	if (ret == 1)
		my_cd(token->args, env);
	if (ret == 2)
		my_pwd();
	if (ret == 3)
		my_env(*env);
	if (ret == 4)
		my_exit(token->args, token->num_args);
	if (ret == 5)
		my_echo(token->args);
	if (ret == 6)
		my_unset(token->args, env);
	if (ret == 7)
		my_export(token->args, env);
	return (1);
}

int	is_equal_sign(char *arg, int i, char c)
{
	while (arg[i])
	{
		if (arg[i] == c)
			return (1);
		else
			i--;
	}
	return (0);
}

int	printf_error(char *msg, int code)
{
	ft_putstr_fd(msg, 2);
	g_exitcode = code;
	return (1);
}
