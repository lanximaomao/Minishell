#include "minishell.h"

void init_input(t_input *input)
{
	input->temp_line = NULL;
	input->quote_type = 0;
	input->pipe_sign = 0;
	input->redir_sign = 0;
}

// check if the quote is closed or not
int handle_quote(char *line, int i, int *len)
{
	int count = 1;
	char quote = line[i];
	while (line[++i] != quote)
	{
		if (!line[i])
			return (-1); // no cloced quote
		count++;
	}
	*len += count;
	return (i);
}

int handle_token(t_input *input, char *line, int i, int *len)
{
	*len = 0; //  length of the substring that needs to be extracted currently.
	while (!(line[i] == ' ' || (line[i] > 8 && line[i] < 14)) && line[i] && ++(*len))
	{
		if ((line[i] == '|' || line[i] == '<' || line[i] == '>'))
		{
			if (line[i] == '|')
				input->pipe_sign = 1; // left pipe
			else if (line[i] == '<' && line[i + 1] != '<')
				input->redir_sign = 1; // infile, <
			else if (line[i] == '<' && line[i + 1] == '<') // 函数内部可以直接判断后面有没有东西，没有的话syntax error，或者在parser上做
				input->redir_sign = 2; // heredoc, <<
			else if (line[i] == '>' && line[i + 1] != '>')
				input->redir_sign = 3; // outfile, >
			else if (line[i] == '>' && line[i + 1] == '>')
				input->redir_sign = 4; // append, >>
			(*len)--;
			break;
		}
		else if (((line[i] == '\'' && (input->quote_type = 1))
				|| (line[i] == '\"' && (input->quote_type = 2)))
				&& ((i = handle_quote(line, i, len)) == -1))
			ft_error("Syntax error: quote not closed.", SYNTAX);
		i++;
	}
	return i;
}

// after split, trim the quotes in input->temp_line
char *trim_quote(char *temp_line, int quote_type)
{
	char quote;
	char *trim_line;
	int i = -1;
	int len = 0;

	if (quote_type == 1)
		quote = '\'';
	else
		quote = '\"';
	trim_line = (char *)malloc(sizeof(char) * (ft_strlen(temp_line) - 1));
	if (!trim_line)
		ft_error("Malloc failed", MALLOC);
	while (temp_line[++i])
	{
		if (temp_line[i] != quote)
			trim_line[len++] = temp_line[i];
	}
	free(temp_line);
	temp_line = NULL;
	trim_line[len] = '\0';
	return (trim_line);
}

t_list *get_linelst(char *line, t_list *line_lst, int i) // i = -1
{
	int len;
	t_input *input;
	t_list *node;

	while (line[++i])
	{
		if (!(line[i] == ' ' || (line[i] > 8 && line[i] < 14)))
		{
			if (!(input = (t_input *)malloc(sizeof(t_input))))
				ft_error("Malloc failed", MALLOC);
			init_input(input);
			i = handle_token(input, line, i, &len);
			if (!(input->temp_line = ft_substr(line, i - len, len))) // Extract the substring and store it into the data structure of a lst node.
				ft_error("Malloc failed", MALLOC);
			if (input->quote_type)
				input->temp_line = trim_quote(input->temp_line, input->quote_type); // trim the quote & dquote, free the 1st argument temp_line in this function.
			if (input->redir_sign == 2 || input->redir_sign == 4)
				i += 1; // skip two characters, the other++ in the condition of while loop
			if (!(node = ft_lstnew((t_input *)input)))
				ft_error("Malloc failed", MALLOC);
			ft_lstadd_back(&line_lst, node);
		}
	}
	return (line_lst);
}

