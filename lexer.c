#include "minishell.h"

void	free_input(t_input *input)
{
	if (input != NULL)
	{
		if (input->temp_line != NULL)
		{
			free(input->temp_line);
			input->temp_line = NULL;
		}
		input->quote_type = 0;
		free(input);
		input = NULL;
	}
}

void init_input(t_input *input)
{
	input->temp_line = NULL;
	input->quote_type = 0;
}

char *handle_char(char *line, char c, int *len)
{
	int count = 1;
	line++;
	while (*line != c && *line && ++count)
		line++;
	*len += count;
	return (line);
}

t_list *get_linelst(char *line)
{
	t_list *line_lst = NULL;
	t_list *node = NULL;
	int len;
	t_input *input;

	if (line == NULL)
		return NULL;
	if (ft_strnstr(line, "&&", ft_strlen(line)) || ft_strnstr(line, "||", ft_strlen(line)))
	{
		ft_printf("\033[1;31mError!\033[0m: %s", "&& or || is handled in BONUS PART\n");
		return NULL;
	}
	while (*line)
	{
		if (!(*line == ' ' || (*line > 8 && *line < 14)))
		{
			len = 0;
			if (!(input = (t_input *)malloc(sizeof(t_input))))
			{
				ft_printf("\033[1;31mError!\033[0m: %s", "Malloc failed\n");
				return (NULL);
			}
			init_input(input);
			while (!(*line == ' ' || (*line > 8 && *line < 14)) && *line && ++len)
			{
				// handle the pipe
				if (*line == '|')
				{
					line--; // if the pipe is the 1st character, then segmentation fault. So change to index
					if (!(*line == ' ' || (*line > 8 && *line < 14))) // "****|"
						len--;
					line++;
					break;
				}
				if (*line == '\'' && (input->quote_type = 1) || *line == '\"' && (input->quote_type = 2))
					line = handle_char(line, *line, &len);
				line++;
			}
			printf("len: %d\n", len);
			input->temp_line = ft_substr(line - len, 0, len);
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
		} else
			line++;
	}
	return (line_lst);
}

int main(int argc, char **argv)
{
	t_list *line_lst = NULL;
	t_input *input;

	line_lst = get_linelst(argv[1]);
	// ft_printf("%s\n", argv[1]);
	// ft_printf("%s\n", ((t_input *)line_lst->content)->temp_line);
	// ft_printf("%d\n", input->quote_type);
	while (line_lst)
	{
		ft_printf("%s\n", ((t_input *)line_lst->content)->temp_line);
		ft_printf("%d\n", ((t_input *)line_lst->content)->quote_type);
		line_lst = line_lst->next;
	}
	return (0);
}


