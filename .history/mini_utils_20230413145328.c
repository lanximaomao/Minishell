#include "minishell.h"

void error(char* msg, int error_code)
{
	perror(msg);
	exit(error_code);
}
// error msgs for project
void ft_error(char* msg)
{
	ft_printf("\033[1;31mError\n\033[0m: %s\n", msg);
	ft_printf("%s\n", msg);
}

void close(int *fd, int num_fd)
{
	int i;
	i = 0;
	while (i < num_fd)
		close(fd[i++]);
	return ;
}

// free p2p
void free_p2p(char **p2p, int num_p2p)
{
	while (num_p2p--)
		free(p2p[num_p2p]);
	free(p2p);
}

int count_quote(char *str)
{
	int count_quote = 0;
	
	while (*str)
	{
		if (*str == '\'' || *str == '\"')

	}
}
