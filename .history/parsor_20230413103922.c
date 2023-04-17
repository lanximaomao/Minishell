#include "minishell.h"

void parser(char *line)
{
	int i = 0;
	int count = 0;
	char *line_split = NULL;

	if (line == NULL)
		return ;
	if (ft_substr)
		return ;
	line_split = ft_split(line, '|');
	while (line_split[i])
	{
		if (line_split[i] == NULL)
			break;
		count++;
		i++;
	}


	free(line_split);


}

// < infile ls -l | wc -l > outfile
