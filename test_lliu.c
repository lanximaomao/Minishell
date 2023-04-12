#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

int main() {
  char *line;
  while ((line = readline("Enter a command: ")) != NULL) {
    add_history(line);
    printf("You entered: %s\n", line);
	if (ft_strncmp(line, "exit", 4) == 0)
	{
		free(line);
		break ;
	}
    free(line);
  }
  return 0;
}
