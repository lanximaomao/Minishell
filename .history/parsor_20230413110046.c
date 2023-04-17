#include "minishell.h"

void parser(char *line)
{
	int i = 0;
	int count = 0;
	char *line_split = NULL;

	if (line == NULL)
		return ;
	if (ft_strnstr(line, "||", ft_strlen(line)) || ft_strnstr(line, "||", ft_strlen(line)))
	{
		ft_printf("\033[1;31mError: \n\033[0m");
		return ;
	}
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
