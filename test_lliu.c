#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "ft_printf.h"
#include "libft.h"

void ft_error(char* msg)
{
	ft_printf("\033[1;31mError! \033[0m%s", msg);
	return ;
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

char **handle_heredoc(char *eof)
{
	int i = 0;
	int count = 0;
	char **heredoc;

	heredoc = (char **)ft_calloc(1, sizeof(char *)); // for (char **) terminated with NULL
	if (!heredoc)
		return (NULL);

	while(1)
	{
		heredoc = (char **)ft_realloc(heredoc, (count + 1) * sizeof(char *), (count + 2) * sizeof(char *)); // for the next readline;
		if (!heredoc)
		{
			ft_error("malloc error.\n");
			return (NULL);
		}
		heredoc[i] = readline("heredoc >> ");
		if (!heredoc[i])
		{
			free(heredoc);
			ft_error("readline error.\n");
			return (NULL);
		}
		count++;
		if (ft_strncmp(heredoc[i], eof, ft_strlen(heredoc[i])) == 0)
		{
			free(heredoc[i]);
			heredoc[i] = NULL;
			break;
		}
	}
	return (heredoc);
}

int main(int argc, char **argv) {
	int i = 0;
	char **heredoc;

	while (1)
	{
		char *line = readline("minishell$ ");
		if (ft_strnstr(line, ">>", ft_strlen(line)) != NULL)
		{
			ft_printf("test\n");
			heredoc = handle_heredoc("eof");
			while(*heredoc)
			{
				printf("%s\n", *heredoc++);
			}
		}
		add_history(line);
		printf("You entered: %s\n", line);

	}

	return 0;
}
