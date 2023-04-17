#include "minishell.h"



char **get_tokens(char *line)
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
		{
			ft_printf("\033[1;31mError\n\033[0m: %s\n", "parse error near `|'\n");
			return ;
		}
		line_input->cmd_tokens = ft_split(line_input->cmd_segment[i], ' ');
		i++;
	}
	free_p2p(line_input->cmd_segment);
	return (line_input->cmd_tokens);
}

void parse_tokens(char **line_input->cmd_tokens)
{
	int i = 0;
	int j = 0;

	while (line_input->cmd_tokens[i])
	{
		if (line_input->cmd_tokens[i] == "<")
		{
			if (open(line_input->cmd_tokens[i + 1], O_RDONLY) == -1)
				error("Open the input of redirection failed \n", 1);
		}

		i++;
	}
}
// < infile ls -l | wc -l > outfile
