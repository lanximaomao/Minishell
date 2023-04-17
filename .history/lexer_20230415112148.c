#include "minishell.h"

// error msgs for project
void ft_error(char* msg)
{
	ft_printf("\033[1;31mError! \033[0m%s\n", msg);
	return ;
}

void init_input(t_input *input)
{
	input->temp_line = NULL;
	input->quote_type = 0;
	input->pipe_sign = 0;
	input->redir_sign = 0;
}

int handle_char(char *line, int i, int *len)
{
	int count = 1;
	char quote = line[i];
	while (line[++i] != quote)
	{
		if (line[i] == '\0')
			return (-1); // no cloced quote
		count++;
	}
	*len += count;
	return (i);
}

char *trim_quote(char *temp_line, char quote)
{
	char *trim_line;
	int i = -1;
	int len = 0;

	trim_line = (char *)malloc(sizeof(char) * (ft_strlen(temp_line) - 1));
	if (!trim_line)
		return (NULL);
	while (temp_line[++i])
	{
		if (temp_line[i] != quote)
			trim_line[len++] = temp_line[i];
	}
	trim_line[len] = '\0';
	return (trim_line);
}

t_list *get_linelst(char *line)
{
	t_list *line_lst = NULL;
	t_list *node = NULL;
	int i = -1;
	int len;
	t_input *input;

	if (line == NULL)
		return NULL;
	if (ft_strnstr(line, "&&", ft_strlen(line)) || ft_strnstr(line, "||", ft_strlen(line)))
	{
		ft_error("&& or || is handled in BONUS PART.");
		return NULL;
	}
	while (line[++i])
	{
		if (!(line[i] == ' ' || (line[i] > 8 && line[i] < 14)))
		{
			len = 0; //  length of the substring that needs to be extracted currently.
			if (!(input = (t_input *)malloc(sizeof(t_input))))
			{
				ft_error("Malloc failed.");
				return (NULL);
			}
			init_input(input);
			while (!(line[i] == ' ' || (line[i] > 8 && line[i] < 14)) && line[i] && ++len)
			{
				// split the pipe in two situations: "**|" and " |"
				if (line[i] == '|')
				{
					input->pipe_sign = 1; // left pipe
					// len--; // 为了不把｜给添加到temp_line里main
					// i--; // 直接break出来，就没有执行下面的i++；所以不要i--
					break;
				}
				if (line[i] == '<') // 函数内部可以直接判断后面有没有东西，没有的话syntax error，或者在parser上做
				{
					if (line[i + 1] == '<' && line[i + 2] != '<')
						input->redir_sign = 2; // heredoc
					else if (line[i + 1] != '<')
						input->redir_sign = 1; // infile
					else
					{
						ft_error("syntax error: more then two '<'.");
						return (NULL);
					}
					// len--;
					break;
				}
				if (line[i] == '>')
				{
					if (line[i + 1] == '>' && line[i + 2] != '>')
						input->redir_sign = 4; // append
					else if (line[i + 1] != '>')
						input->redir_sign = 3; // outfile
					else
					{
						ft_error("syntax error: more then two '>'.");
						return (NULL);
					}
					// len--;
					break;
				}
				if ((line[i] == '\'' && (input->quote_type = 1)) || (line[i] == '\"' && (input->quote_type = 2)))
				{
					if ((i = handle_char(line, i, &len)) == -1)
					{
						ft_error("syntax error: quote not closed.");
						return (NULL);
					}
				}
				i++;
			}
			input->temp_line = ft_substr(line, i - len, len); // Extract the substring and store it into the data structure of a lst node.
			if (!input->temp_line)
			{
				ft_error("Malloc failed.");
				return (NULL);
			}
			if (input->quote_type == 1)
				input->temp_line = trim_quote(input->temp_line, '\''); // trim the quote
			else if(input->quote_type == 2)
				input->temp_line = trim_quote(input->temp_line, '\"'); // trim the double quote
			if (input->pipe_sign == 1 || input->redir_sign == 1 || input->redir_sign == 3) // 为了不死循环，正确存储temp_line（without the pipe）后向｜的下一位移动
				i++; // skip one character
			if (input->redir_sign == 2 || input->redir_sign == 4)
				i += 2; // skip two characters
			node = ft_lstnew((t_input *)input);
			if (!node)
			{
				ft_error("Malloc failed.");
				return (NULL);
			}
			ft_lstadd_back(&line_lst, node);
		}
	}
	return (line_lst);
}


// ***** remember to free input after parsing *****

int main(int argc, char **argv)
{
	t_list *line_lst = NULL;
	t_input *input;
	char *line;

	while (1)
	{
		line = readline("minishell\033[31m$\033[0;39m ");
		add_history(line);

		line_lst = get_linelst(line);
		while (line_lst)
		{
			ft_printf("%s\n", ((t_input *)line_lst->content)->temp_line);
			ft_printf("%d\n", ((t_input *)line_lst->content)->redir_sign);
			line_lst = line_lst->next;
		}
	}
	return (0);
}


