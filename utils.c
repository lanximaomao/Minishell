// for lexer and parser

#include "minishell.h"

// error msgs for project
void ft_error(char* msg)
{
	printf("\033[1;31mError! \033[0m%s", msg);
	return ;
}
// lexer.c
void init_input(t_input *input)
{
	input->temp_line = NULL;
	input->quote_type = 0;
	input->pipe_sign = 0;
	input->redir_sign = 0;
}
// parser
void init_token(t_token *token)
{
	token->cmd = NULL;
	token->args = NULL;
	token->infile = NULL;
	token->outfile = NULL;
	token->output_type = NULL;
	token->num_args = 0;
	token->num_infile = 0;
	token->num_outfile_type = 0;

}

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

void free_p2p(char **p2p, int num_p2p)
{
	while (num_p2p--)
	{
		if (p2p[num_p2p] != NULL)
		{
			free(p2p[num_p2p]);
			p2p[num_p2p] = NULL;
		}
	}
	free(p2p);
	p2p = NULL;
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

void free_token(t_token *token, int num_args, int num_infile, int num_outfile_type)
{
	if (token != NULL)
	{
		if (token->cmd != NULL)
		{
			free(token->cmd);
			token->cmd = NULL;
		}
		if (token->args != NULL)
			free_p2p(token->args, num_args);
		if (token->infile != NULL)
			free_p2p(token->infile, num_infile);
		if (token->outfile != NULL)
			free_p2p(token->outfile, num_outfile_type);
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

