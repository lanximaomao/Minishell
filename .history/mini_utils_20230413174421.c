#include "minishell.h"

void	error(char *msg, int error_code)
{
	perror(msg);
	exit(error_code);
}
// error msgs for project
void	ft_error(char *msg)
{
	ft_printf("\033[1;31mError\n\033[0m: %s\n", msg);
	ft_printf("%s\n", msg);
}

void	close(int *fd, int num_fd)
{
	int	i;

	i = 0;
	while (i < num_fd)
		close(fd[i++]);
	return ;
}

// free p2p
void	free_p2p(char **p2p, int num_p2p)
{
	while (num_p2p--)
		free(p2p[num_p2p]);
	free(p2p);
}

int	count_char(char *str, char char_type)
{
	int	count_char;

	count_char = 0;
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
		free(input);
		input = NULL;
	}
	input->quote_type = 0;
}
