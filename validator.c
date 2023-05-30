#include "minishell.h"
#include "validator.h"

int	validator(t_list *line_lst)
{
	t_list	*current;
	t_list	*subsequent;
	t_input	*current_input;
	t_input	*subsequent_input;

	current = line_lst;
	subsequent_input = NULL;
	while (current)
	{
		subsequent = current->next;
		current_input = (t_input *)(current->content);
		if (subsequent)
			subsequent_input = (t_input *)(subsequent->content);
		if (current_input->quote_type == 0)
		{
			if (check_pipe(current_input, subsequent_input, subsequent) == -1)
				return (-1);
			if (check_double(current_input, subsequent_input, subsequent) == -1)
				return (-1);
			if (check_redir(current_input, subsequent) == -1)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}

/*
** error 1 covers cases like: | or ls |
** error 2 covers cases like: | pwd
*/
int	check_pipe(t_input *in1, t_input *in2, t_list *subsequent)

{
	if (in1->pipe_sign == 1 && subsequent == NULL)
	{
		ft_error("Syntax error: how dare you? ", SYNTAX, 1);
		return (-1);
	}
	if (in1->pipe_sign == 1 && ft_strncmp(in1->temp_line, "", 1) == 0)
	{
		ft_error("Syntax error: don't fool me around! ", SYNTAX, 1);
		return (-1);
	}
	return (0);
}

/* error 02 covers cases like ls <> pwd */
int	check_double(t_input *in1, t_input *in2, t_list *subsequent)
{
	if (ft_strncmp(in1->temp_line, "", 1) == 0)
	{
		if (subsequent && ft_strncmp(in2->temp_line, "", 1) == 0)
		{
			ft_error("Syntax error: Aren't you an idiot? ", SYNTAX, 1);
			return (-1);
		}
	}
	return (0);
}

/* error redirection if no filename is found after redirection sign */
int	check_redir(t_input *in1, t_list *subsequent)
{
	if (in1->redir_sign != 0)
	{
		if (subsequent == NULL)
		{
			ft_error("Syntax error: Don't mess up with me, idiot!", SYNTAX, 1);
			return (-1);
		}
	}
	return (0);
}
