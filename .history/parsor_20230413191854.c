#include "minishell.h"



t_token *parse_tokens(char **line_input->cmd_tokens)
{
	int i = 0;
	int fd = 0;
	t_token *token;

	while (line_input->cmd_tokens[i])
	{
		if (line_input->cmd_tokens[i] == "<")
		{
			token->*infile++ = line_input->cmd_tokens[i + 1];
			// if ((fd = open(line_input->cmd_tokens[i + 1], O_RDONLY)) == -1)
			// 	error("Open the input file of redirection failed!\n", 1);
			// dup2(fd, STDIN_FILENO);
			i++;
		} else if (line_input->cmd_tokens[i] == ">")
		{
			token->*outfile++ = line_input->cmd_tokens[i + 1];
			i++;
		} else if (line_input->cmd_tokens[i] == "<<")
		{

		} else if (line_input->cmd_tokens[i] == ">>")
		{
			sign_out = 1;

		}
		i++;
	}
	return (token);
}
// < infile 'ls' "-l" | wc -l > outfile
\n \t 
