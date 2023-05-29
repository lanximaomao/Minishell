# include "minishell.h"

// part of code is from handle_args_expand

// ! check for unclosed quotes is in lexer

//check for unclosed pipe
//check for incomplete redir
// to be add: <f1>
// segfault: << f1 >


int validator(t_list *line_lst)
{
	t_list *tmp;
	t_input *input;

	tmp = line_lst;
	while (tmp)
	{
		input = (t_input *)(tmp->content);
		// ls |
		if (input->pipe_sign == 1 && tmp->next && ((t_input*)(tmp->next->content))->pipe_sign == 1)
		{
			ft_error("Syntax error 01", SYNTAX, 1);
			return (-1);
		}
		// check '| |' '< >>'
		if (ft_strncmp(input->temp_line, "", 1) == 0) // same
		{
			if(tmp->next && ft_strncmp(((t_input*)(tmp->next->content))->temp_line, "", 1)==0)
			{
				ft_error("Syntax error 02", SYNTAX, 1);
				return (-1);
			}
			else
			{
				if (tmp->next && ft_strncmp(((t_input *)tmp->next->content)->temp_line, "", 1)==0)
				{
					ft_error("Syntax error 03", SYNTAX, 1);
					return (-1);
				}
			}
		}
		// <, >, <<, >>,
		if (((t_input *)line_lst->content)->redir_sign != 0)
		{
			if (line_lst->next == NULL) // handle error: each redirection file cannot be empty, parse error
			{
				ft_error("Syntax error 04", SYNTAX, 1); // modify later by Lin's signal_handler
				return(-1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
