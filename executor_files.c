#include "builtin.h"
#include "executor.h"

int	handle_io(t_token *token, int cmd_order, int size, int *fd_pipe)
{
	if (size == 1)
	{
		token->fd_in = dup(0);
		token->fd_out = dup(1);
		return (get_file_fd(token));
	}
	if (cmd_order != 0)
		token->fd_in = fd_pipe[0];
	if (cmd_order != size - 1 && pipe(fd_pipe) == -1)
		ft_error(" minishell: error in creating pipes.\n", 4, 0);
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

int	get_file_fd(t_token *tokens)
{
	int	i;
	int	count_in;
	int	count_out;

	i = -1;
	count_in = 0;
	count_out = 0;
	while (tokens->file_redir && tokens->file_redir[++i])
	{
		if (tokens->file_type[i] == 3)
		{
			if (get_infile_fd(tokens, i, &count_in) == -1)
				return (-1);
		}
		else
		{
			if (get_outfile_fd(tokens, i, &count_out))
				return (-2);
		}
	}
	return (0);
}

int	get_infile_fd(t_token *tokens, int i, int *count_in)
{
	close(tokens->fd_in);
	tokens->fd_in = open(tokens->file_redir[i], O_RDONLY);
	if (tokens->fd_in < 0)
	{
		ft_error(" minishell:", FILE_OP, 1);
		g_exitcode = 1;
		return (-1);
	}
	(*count_in)++;
	if ((*count_in) != tokens->num_infile)
		close(tokens->fd_in);
	return (0);
}

int	get_outfile_fd(t_token *tokens, int i, int *count_out)
{
	close(tokens->fd_out);
	if (tokens->file_type[i] == 1)
		tokens->fd_out = open(tokens->file_redir[i],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		tokens->fd_out = open(tokens->file_redir[i],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (tokens->fd_out < 0)
	{
		ft_error(" minishell:", FILE_OP, 1);
		g_exitcode = 1;
		return (-2);
	}
	(*count_out)++;
	if ((*count_out) != tokens->num_outfile)
		close(tokens->fd_out);
	return (0);
}
