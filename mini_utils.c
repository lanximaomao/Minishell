#include "minishell.h"

/*
 combine this error function
 exit(error_code)
 # define MALLOC 1
 # define FILE_OP 2
 # define SYNTAX 3
 # define FUNC 4
 error_code: <= 2 for system perror(malloc, file_err...)
 others for the mini_error(syntax, parse_err)
*/

void ft_error(char* msg, int error_code, int flag) // flag 0 means exit, flag 2 means return
{
	if (error_code <= 2)
		perror(msg);
	else
	{
		ft_putstr_fd(msg, 2);
		write(2, "\n", 1);
	}
	if (flag == 0)
	{
		g_exitcode = error_code;
		exit(g_exitcode);
	}
}

int free_str(char *str)
{
	free(str);
	str = NULL;
	return (1);
}

void free_char(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

void free_input(t_input *input)
{
	if (input != NULL)
	{
		if (input->temp_line != NULL)
		{
			free(input->temp_line);
			input->temp_line = NULL;
		}
		input->quote_type = 0;
		input->pipe_sign = 0;
		input->redir_sign = 0;
		free(input);
		input = NULL;
	}
}

void free_tokens(t_token *tokens, int num_args, int num_infile, int num_outfile_type)
{
	if (tokens != NULL)
	{
		if (tokens->cmd != NULL)
		{
			free(tokens->cmd);
			tokens->cmd = NULL;
		}
		if (tokens->args != NULL)
			free_char(tokens->args);
		if (tokens->infile != NULL)
			free_char(tokens->infile);
		if (tokens->outfile != NULL)
			free_char(tokens->outfile);
		if (tokens->output_type != NULL)
		{
			free(tokens->output_type);
			tokens->output_type = NULL;
		}
		num_args = 0;
		num_infile = 0;
		num_outfile_type = 0;
		free(tokens);
		tokens = NULL;
	}
}
