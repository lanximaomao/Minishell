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

	while (line)
	{
		(t_input *)line_lst->content->temp_line
	}
	return (token);
}
// < infile 'ls' "-l" | wc -l > outfile

