#include "minishell.h"

/*
** if: the | or < is the last character
** else if: if current is pipe, error occurs
** when the next and next next are both empty
** else if: if current does not contain a pipe
** error occurs when this and the next are both empty lines
*/
static int	handle_parse_error(t_list *line_lst, int sign)
{
	if (sign == 1 && (((t_input *)line_lst->content)->pipe_sign == 1
			|| ((t_input *)line_lst->content)->redir_sign != 0))
	{
		ft_error("Syntax error: parse error", SYNTAX, 1);
		return (-1);
	}
	else if (sign == 2 && line_lst->next->next
		&& !ft_strncmp(((t_input *)line_lst->next->content)->tmp_line, "", 1)
		&& !ft_strncmp(((t_input *)line_lst->next->next->content)->tmp_line,
			"", 1))
	{
		ft_error("Syntax error: parse error", SYNTAX, 1);
		return (-1);
	}
	else if (sign == 3 && line_lst->next
		&& !ft_strncmp(((t_input *)line_lst->next->content)->tmp_line, "", 1))
	{
		ft_error("Syntax error: parse error", SYNTAX, 1);
		return (-1);
	}
	return (0);
}

int	validator(t_list *line_lst)
{
	t_input		*input;

	while (line_lst)
	{
		input = (t_input *)line_lst->content;
		if (!(line_lst->next))
			if (handle_parse_error(line_lst, 1) == -1)
				return (-1);
		if (!ft_strncmp(input->tmp_line, "", 1))
		{
			if (input->pipe_sign == 1)
			{
				if (handle_parse_error(line_lst, 2) == -1)
					return (-1);
			}
			else
				if (handle_parse_error(line_lst, 3))
					return (-1);
		}
		line_lst = line_lst->next;
	}
	return (0);
}
