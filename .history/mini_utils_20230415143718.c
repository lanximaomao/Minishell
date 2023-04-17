#include "minishell.h"

void error(char* msg, int error_code)
{
	perror(msg);
	exit(error_code);
}


void close(int *fd, int num_fd)
{

}

// free p2p
void free_p2p(char **p2p, int num_p2p)
{
	while (num_p2p--)
		free(p2p[num_p2p]);
	free(p2p);
}

int count_char(char *str, char char_type)
{
	int count_char = 0;

	while (*str)
	{
		if (*str == char_type)
			count_char++;
		str++;
	}
	return (count_char);
}

void	free_input(t_input *input)
{
	if (input != NULL)
	{
		if (input->temp_line != NULL)
		{
			free(input->temp_line);
			input->temp_line = NULL;
		}
		input->quote_type = 0;
		free(input);
		input = NULL;
	}
}
