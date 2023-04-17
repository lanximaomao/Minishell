#include "minishell.h"

void parser(char *line)
{
	char *line_split = NULL;

	line_split = ft_strplit(line, ' ');
	ft_printf("You entered: %s\n", line);


}
