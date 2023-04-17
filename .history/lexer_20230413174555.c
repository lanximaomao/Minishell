#include "minishell.h"

void handle_quote()
{

}


t_list *get_linelst(char *line)
{
	t_list *line_lst = NULL;
	t_list *node;
	int i;
	int len;
	t_input *input;

	if (line == NULL)
		return ;
	if (ft_strnstr(line, "&&", ft_strlen(line)) || ft_strnstr(line, "||", ft_strlen(line)))
	{
		ft_printf("\033[1;31mError\n\033[0m: %s\n", "&& or || is handled in BONUS PART\n");
		return ;
	}
	while (*line)
	{
		i = 0;
		if (!(*line == ' ' || (*line > 8 && *line < 14)))
		{
			len = 0;
			if (*line == '\'' && (in = 1))
			{
				while (*line != '\'' && *line && ++len)
					line++;
			} else if (*line == '\"' && (sign_dquote = 1))
			{
				while (*line != '\"' && *line && ++len)
					line++;
			} else {
				while (*line != ' ' && *line && ++len)
					line++;
			}
			input->temp_line[i] = ft_substr(line - len, 0, len);
			if (!input->temp_line)
			{
				ft_printf("\033[1;31mError\n\033[0m: %s\n", "Malloc failed\n");
				return (NULL);
			}
			i++;
			node = ft_lstnew(input);
			if (!line_lst)
			{
				ft_printf("\033[1;31mError\n\033[0m: %s\n", "Malloc failed\n");
				return (NULL);
			}
			ft_lstadd_back(&line_lst, node);
			free(input);
			input = NULL;
		} else
			line++;
	}

	return (line_lst);
}
