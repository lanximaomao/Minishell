#include "minishell.h"

void error(char* msg, int error_code)
{
	perror(msg);
	exit(error_code);
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
void free_p2p(char **p2p, int i)
{
	while (i--)
		free(p2p[i]);
	free(p2p);
}

