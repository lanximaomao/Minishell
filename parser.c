#include "minishell.h"
// check the current temp_line has the </>/<</>> or not, return the index or -1
int check_redirection(char *temp_line)
{
	int i = 0;
	while (temp_line[i])
	{
		if (temp_line[i] == '<' || line_lst->temp_line->cmd_tokens[i] == ">" || line_lst->temp_line->cmd_tokens[i] == "<<" || line_lst->temp_line->cmd_tokens[i] == ">>")
		i++;
	}
	return (i);
	return (-1);
}

// input line_lst return tokens, in here, one token is one complete cmd
t_list *parse_tokens(t_list *line_lst)
{
	int i = 0;
	int fd = 0;
	t_list *tokens = NULL;
	t_list *node = NULL;
	t_token *token;

	while (line_lst->temp_line)
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

