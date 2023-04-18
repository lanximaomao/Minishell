#include "minishell.h"

// combine this error function
void error(char* msg, int error_code)
{
	perror(msg);
	exit(error_code);
}

// error msgs for project
void ft_error(char* msg)
{
	printf("\033[1;31mError! \033[0m%s", msg);
	return ;
}

// add this function to libft_42 after testing
char *ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void *new_ptr = NULL;

	if (!new_size)
	{
		free(ptr);
		return NULL;
	}
	new_ptr = (void *)ft_calloc(new_size, sizeof(void));
	if (!new_ptr)
		return NULL;

	if (ptr != NULL)
	{
		ft_memcpy(new_ptr, ptr, old_size);
		free(ptr);
		ptr = NULL;
	}
	return new_ptr;
}

// free char **
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

void free_tokens(t_token *token, int num_args, int num_infile, int num_outfile_type)
{
	if (token != NULL)
	{
		if (token->cmd != NULL)
		{
			free(token->cmd);
			token->cmd = NULL;
		}
		if (token->args != NULL)
			free_char(token->args);
		if (token->infile != NULL)
			free_char(token->infile);
		if (token->outfile != NULL)
			free_char(token->outfile);
		if (token->output_type != NULL)
		{
			free(token->output_type);
			token->output_type = NULL;
		}
		num_args = 0;
		num_infile = 0;
		num_outfile_type = 0;
		free(token);
		token = NULL;
	}
}
