#include "minishell.h"

void error(char* msg, int error_code)
{
	perror(msg);
	exit(error_code);
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
