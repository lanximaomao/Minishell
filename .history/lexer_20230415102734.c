#include "minishell.h"



void init_input(t_input *input)
{
	input->temp_line = NULL;
	input->quote_type = 0;
	input->pipe_sign = 0;
}

int handle_char(char *line, int i, int *len)
{
	int count = 1;
	char quote = line[i];
	while (line[++i] != quote && line[i])
		count++;
	*len += count;
	return (i);
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
		ft_printf("\033[1;31mError!\033[0m: %s", "&& or || is handled in BONUS PART\n");
		return NULL;
	}
	while (line[++i])
	{
		if (!(line[i] == ' ' || (line[i] > 8 && line[i] < 14)))
		{
			len = 0; //  length of the substring that needs to be extracted currently.
			if (!(input = (t_input *)malloc(sizeof(t_input))))
			{
				ft_printf("\033[1;31mError!\033[0m: %s", "Malloc failed\n");
				return (NULL);
			}
			init_input(input);
			while (!(line[i] == ' ' || (line[i] > 8 && line[i] < 14)) && line[i] && ++len)
			{
				// split the pipe in two situations: "**|" and " |"
				if (line[i] == '|')
				{
					input->pipe_sign = 1; // left pipe
					len--; // 为了不把｜给添加到temp_line里main
					// i--; // 直接break出来，就没有执行下面的i++；所以不要i--
					break;
				}
				if (line[i] == '<') // 函数内部可以直接判断后面有没有东西，没有的话syntax error，或者在parser上做
				{
					if (line[i + 1] == '<' && line[i + 2] != '<')
						input->redir_sign = 2; // heredoc
					
					input->redir_sign = 1; // infile
					len--;
					break;
				}
				if (line[i] == '>')
				{
					fi (line[i + 1] == '>')
					{
						input->redir_sign = 4; // append
					}
					input->redir_sign = 3; // outfile
					len--;
					break;
				}

				if (line[i] == '\'' && (input->quote_type = 1) || line[i] == '\"' && (input->quote_type = 2))
					i = handle_char(line, i, &len);
				i++;
			}
			input->temp_line = ft_substr(line, i - len, len); // Extract the substring and store it into the data structure of a lst node.
			if (input->pipe_sign == 1) // 为了不死循环，正确存储temp_line（without the pipe）后向｜的下一位移动
				i++;
			// printf("len: %d\n", len);
			if (!input->temp_line)
			{
				ft_printf("\033[1;31mError!\033[0m: %s", "Malloc failed\n");
				return (NULL);
			}
			node = ft_lstnew((t_input *)input);
			if (!node)
			{
				ft_printf("\033[1;31mError!\033[0m: %s", "Malloc failed\n");
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

	line_lst = get_linelst(readline("minishell$ "));
	while (line_lst)
	{
		ft_printf("%s\n", ((t_input *)line_lst->content)->temp_line);
		ft_printf("%d\n", ((t_input *)line_lst->content)->quote_type);
		line_lst = line_lst->next;
	}
	return (0);
}


