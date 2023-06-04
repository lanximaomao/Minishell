#include "minishell.h"

/*
 exit(error_code)
 # define MALLOC 1
 # define FILE_OP 2
 # define SYNTAX 3
 # define FUNC 4
 error_code: <= 2 for system perror(malloc, file_err...)
 others for the mini_error(syntax, parse_err)
 flag 0 means exit, flag 1 means return
*/

void	ft_error(char *msg, int error_code, int flag)
{
	if (error_code <= 2)
		perror(msg);
	else
	{
		ft_putstr_fd(msg, 2);
		write(2, "\n", 1);
	}
	if (flag == 0)
	{
		g_exitcode = error_code;
		exit(g_exitcode);
	}
}

/*
** if: the | or < is the last character
** else if: if current is pipe, error occurs
** when the next and next next are both empty
** else if: if current does not contain a pipe
** error occurs when this and the next are both empty lines
*/

static int	handle_parse_error(int cmd_order, t_list *line_lst, int sign)
{
	if (sign == 1 && (((t_input *)line_lst->content)->pipe_sign == 1 // pwd |
			|| ((t_input *)line_lst->content)->redir_sign != 0)) // pwd >
	{
		ft_error("Syntax error: parse error", SYNTAX, 1);
		return (-1);
	}
	else if ((sign == 2 && ((t_input *)line_lst->next->content)->pipe_sign == 1) // | |
		|| (sign == 2 && cmd_order == 1 // | pwd
		&& ft_strncmp(((t_input *)line_lst->next->content)->tmp_line, "", 1))
		|| (sign == 2 && line_lst->next->next // | < > pwd
		&& !ft_strncmp(((t_input *)line_lst->next->content)->tmp_line, "", 1)
		&& !ft_strncmp(((t_input *)line_lst->next->next->content)->tmp_line, "", 1)))
	{
		ft_error("Syntax error: parse error", SYNTAX, 1);
		return (-1);
	}
	else if (sign == 3 && line_lst->next
		&& !ft_strncmp(((t_input *)line_lst->next->content)->tmp_line, "",
			1))
	{
		ft_error("Syntax error: parse error", SYNTAX, 1);
		return (-1);
	}
	return (0);
}

int	validator(t_list *line_lst)
{
	int		i;
	t_input	*input;

	i = 1;
	while (line_lst)
	{
		input = (t_input *)line_lst->content;
		if (!(line_lst->next))
			if (handle_parse_error(i, line_lst, 1) == -1)
				return (-1);
		if (!ft_strncmp(input->tmp_line, "", 1))
		{
			if (input->pipe_sign == 1)
			{
				if (handle_parse_error(i, line_lst, 2) == -1)
					return (-1);
			}
			else if (handle_parse_error(i, line_lst, 3))
				return (-1);
		}
		line_lst = line_lst->next;
		i++;
	}
	return (0);
}
