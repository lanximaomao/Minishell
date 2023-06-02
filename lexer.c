#include "minishell.h"

static void	init_input(t_input **input)
{
	*input = (t_input *)ft_calloc(sizeof(t_input), 1);
	if (!input)
		ft_error("Malloc failed", MALLOC, 0);
	(*input)->tmp_line = NULL;
	(*input)->quote_type = 0;
	(*input)->pipe_sign = 0;
	(*input)->redir_sign = 0;
}

/* check if the quote is closed or not */
static int	handle_quote(t_input *input, char *line, int i, int *len)
{
	int		count;
	char	quote;

	count = 1;
	quote = line[i];
	if (quote == '\'')
		input->quote_type = 1;
	else if (quote == '\"')
		input->quote_type = 2;
	while (line[++i] != quote)
	{
		if (!line[i])
		{
			ft_error("Syntax error: quote not closed", SYNTAX, 1);
			return (-1);
		}
		count++;
	}
	*len += count;
	return (i);
}

static int	handle_token(t_input *input, char *line, int i, int *len)
{
	*len = 0;
	while (line[i] != ' ' && line[i] && ++(*len))
	{
		if ((line[i] == '|' || line[i] == '<' || line[i] == '>'))
		{
			if (line[i] == '|')
				input->pipe_sign = 1;
			else if (line[i] == '<' && line[i + 1] != '<')
				input->redir_sign = 1;
			else if (line[i] == '<' && line[i + 1] == '<')
				input->redir_sign = 2;
			else if (line[i] == '>' && line[i + 1] != '>')
				input->redir_sign = 3;
			else if (line[i] == '>' && line[i + 1] == '>')
				input->redir_sign = 4;
			(*len)--;
			break ;
		}
		else if (line[i] == '\'' || line[i] == '\"')
			i = handle_quote(input, line, i, len);
		if (i == -1)
			return (-1);
		i++;
	}
	return (i);
}

static char	*trim_quote(char *tmp_line, int quote_type)
{
	char	quote;
	char	*trim_line;
	int		i;
	int		len;

	i = -1;
	len = 0;
	if (quote_type == 1)
		quote = '\'';
	else if (quote_type == 2)
		quote = '\"';
	else
		return (tmp_line);
	trim_line = (char *)malloc(sizeof(char) * (ft_strlen(tmp_line) - 1));
	if (!trim_line)
		ft_error("Malloc failed", MALLOC, 0);
	while (tmp_line[++i])
	{
		if (tmp_line[i] != quote)
			trim_line[len++] = tmp_line[i];
	}
	free_str(tmp_line);
	trim_line[len] = '\0';
	return (trim_line);
}

t_list	*lexer_get_linelst(char *line, t_list *line_lst, int i)
{
	int		len;
	t_input	*input;

	while (line[++i])
	{
		if (!(line[i] == ' ' || (line[i] > 8 && line[i] < 14)))
		{
			init_input(&input);
			i = handle_token(input, line, i, &len);
			if (i == -1)
				return (NULL);
			input->tmp_line = ft_substr(line, i - len, len);
			if (!input->tmp_line)
				ft_error("Malloc failed", MALLOC, 0);
			input->tmp_line = trim_quote(input->tmp_line, input->quote_type);
			if (input->redir_sign == 2 || input->redir_sign == 4)
				i += 1;
			create_lst(&line_lst, (t_input *)input);
		}
		if (!line[i])
			break ;
	}
	return (line_lst);
}
