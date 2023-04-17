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
			if (*line == '\'' && (input->quote_type = 1))
			{
				while (*line != '\'' && *line && ++len)
					line++;
			} else if (*line == '\"' && (input->quote_type = 2))
			{
				while (*line != '\"' && *line && ++len)
					line++;
			} else {
				while (*line != ' ' && *line && ++len)
					line++;
			}
			if (!(input = (t_input *)malloc(sizeof(t_input))))
			{
				ft_printf("\033[1;31mError!\033[0m: %s", "Malloc failed\n");
				return (NULL);
			}
			input->temp_line = ft_substr(line - len, 0, len);
			if (!input->temp_line)
			{
				ft_printf("\033[1;31mError!\033[0m: %s", "Malloc failed\n");
				return (NULL);
			}
			node = ft_lstnew(input);
			if (!node)
			{
				ft_printf("\033[1;31mError!\033[0m: %s", "Malloc failed\n");
				return (NULL);
			}
			ft_lstadd_back(&line_lst, node);
			free_input(input);
			input = NULL;
		} else
			line++;
	}
	return (line_lst);
}

int main(int argc, char **argv)
{
	t_input *input;
	t_list *line_lst = NULL;

	input = (t_input *)li
	line_lst = get_linelst(argv[1]);
	// ft_printf("%s\n", argv[1]);
	// ft_printf("%s\n", ((t_input *)line_lst->content)->temp_line);
	ft_printf("%d\n", ((t_input *)line_lst->content)->quote_type);
	// while (line_lst)
	// {
	// 	ft_printf("%s\n", ((t_input *)line_lst->content)->temp_line);
	// 	ft_printf("%d\n", ((t_input *)line_lst->content)->quote_type);
	// 	line_lst = line_lst->next;
	// }
	return (0);
}

