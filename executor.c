#include "builtin.h"
#include "executor.h"

/* return values to be fixed */
int	executor(t_mini *mini, int size)
{
	int				*pid;
	int				*status;
	struct termios	t;

	tcgetattr(0, &t);
	t.c_lflag |= ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
	pid = malloc(sizeof(int) * size);
	if (!pid)
		ft_error(" pid malloc fail", 1, 0);
	status = malloc(sizeof(int) * size);
	if (!status)
		ft_error("status malloc fail", 1, 0);
	if (loop(mini, size, pid) != 1)
		get_exitcode(size, pid, status);
	free(pid);
	free(status);
	return (0);
}

int	loop(t_mini *mini, int size, int *pid)
{
	int		i;
	t_list	*tmp;
	t_token	*token;
	int		fd_pipe[2];
	char	**env_exe;

	i = -1;
	tmp = mini->cmd_lst;
	while (tmp && ++i < size)
	{
		token = (t_token *)tmp->content;
		if (handle_io(token, i, size, fd_pipe) != -1 && cmd_in_main(size, token,
				mini->env) == 0)
			return (1);
		env_exe = env_convert(mini->env);
		if (create_child(pid, i) == 0)
		{
			if (i < size - 1)
				close(fd_pipe[0]);
			cmd_execution_in_child(token, mini, env_exe);
		}
		free_and_close(env_exe, token->fd_in, token->fd_out);
		tmp = tmp->next;
	}
	return (0);
}

int	cmd_in_main(int size, t_token *token, t_list *env)
{
	int	in;
	int	out;

	if (size == 1 && is_builtin(token) > 0)
	{
		in = dup(0);
		out = dup(1);
		dup2(token->fd_in, 0);
		close(token->fd_in);
		dup2(token->fd_out, 1);
		close(token->fd_out);
		run_builtin(token, &env);
		dup2(in, 0);
		close(in);
		dup2(out, 1);
		close(out);
		return (0);
	}
	return (1);
}

void	get_exitcode(int size, int *pid, int *status)
{
	int	i;

	i = 0;
	while (i < size)
	{
		waitpid(pid[i], &status[i], 0);
		if (WIFEXITED(status[size - 1]))
			g_exitcode = WEXITSTATUS(status[i]);
		else if (WIFSIGNALED(status[size - 1]))
			g_exitcode = WTERMSIG(status[i]) + 128;
		i++;
	}
}
