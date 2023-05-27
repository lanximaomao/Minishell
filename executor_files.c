#include "builtin.h"
#include "executor.h"

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
		ft_error(" error in creating pipes.\n", 4);
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
	if (get_infile_fd(token) == -1)
		return (-1);
	if (get_outfile_fd(token) == -2)
		return (-2);
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
			return (-1);
		}
		if (i + 1 < token->num_infile)
			close(token->fd_in);
		i++;
	}
	return (0);
}

int	get_outfile_fd(t_token *token)
{
	int	i;

	i = 0;
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
