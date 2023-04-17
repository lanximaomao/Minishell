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

// free functions
void free_list(t_list *list)
{
	t_list *tmp;
	while (list)
	{
		tmp = list->next;
		free(list->content);
		free(list);
		list = tmp;
	}
	return ;
}
