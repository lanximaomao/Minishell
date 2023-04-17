#include "minishell.h"

void parser(char *line)
{
	int i = 0;
	int count = 0;
	t_input	line_input;

	if (line == NULL)
		return ;
	if (ft_strnstr(line, "&&", ft_strlen(line)) || ft_strnstr(line, "||", ft_strlen(line)))
	{
		ft_printf("\033[1;31mError\n\033[0m: %s\n", "&& or || is handled in BONUS PART\n");
		return ;
	}
	line_input->cmd_segment = ft_split(line, '|');
	// for count the num_cmd
	// while (line_input->cmd_segment[i++])
	// 	count++;
	while (line_input->cmd_segment[i])
	{
		if (line_input->cmd_segment[i] == NULL)
			ft_printf("\033[1;31mError\n\033[0m: %s\n", "parse error near `|'");

		cmd_tokens = ft_split(line_input->cmd_segment[i], ' ');
		i++;
	}

	free(line_split);


}

// < infile ls -l | wc -l > outfile
