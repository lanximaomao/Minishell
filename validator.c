#include "minishell.h"
#include "validator.h"

static int check_first(t_input *in1)
{
	if (in1->pipe_sign == 1 && !ft_strncmp(in1->temp_line, "", 1))
	{
		ft_error("pipe at beginning. ", SYNTAX, 1);
		return (-1);
	}
	return(0);
}

static int check_last(t_input *in1, t_input *in2)
{
	if (in1->pipe_sign == 1 && in2 == NULL)
	{
		ft_error("pipe in the end. ", SYNTAX, 1);
		return (-1);
	}
	return(0);
}

// two consequtive pipe and the line in second one is empty
static int check_two_pipes(t_input *in1, t_input *in2)
{
	if (!in2)
		return(0);
	if (in1->pipe_sign == 1 && in2->pipe_sign == 1 && ft_strncmp(in2->temp_line, "", 1) == 0)
	{
		ft_error("Two pipe in a row. ", SYNTAX, 1);
		return(-1);
	}
	return(0);
}

static int check_two_redir(t_input *in1, t_input *in2)
{
	if (in1->redir_sign != 0 && in2 == NULL)
	{
		ft_error("one redirection in a end. ", SYNTAX, 1);
		return(-1);
	}
	if (in1->redir_sign != 0 && in2->redir_sign != 0 && ft_strncmp(in2->temp_line, "", 1) == 0)
	{
		ft_error("Two redirection in a row. ", SYNTAX, 1);
		return(-1);
	}
	return(0);
}

int	validator(t_list *line_lst)
{
	int		i;
	t_list	*current;
	t_list	*subsequent;
	t_input	*current_input;
	t_input	*subsequent_input;

	i = 1;
	current = line_lst;
	subsequent_input = NULL;
	while (current)
	{
		subsequent = current->next;
		current_input = (t_input *)(current->content);
		printf("cmd=%d, line=%s", i, current_input->temp_line);
		if (current_input->temp_line == NULL)
			printf(" !NULL LINE\n");
		else
			printf(" !NOT NULL\n");
		printf("cmd=%d, pipe=%d\n", i, current_input->pipe_sign);
		printf("cmd=%d, redir=%d\n\n", i, current_input->redir_sign);
		if (subsequent)
			subsequent_input = (t_input *)(subsequent->content);
		if (i == 1 && check_first(current_input) == -1)
			return(-1);
		if (check_last(current_input, subsequent_input) == -1)
			return(-1);
		if (check_two_pipes(current_input, subsequent_input) == -1)
			return(-1);
		if (check_two_redir(current_input, subsequent_input) == -1)
			return(-1);
		//if (check_pipe(current_input, subsequent_input, subsequent) == -1)
		//	return (-1);
		//if (check_double(current_input, subsequent_input, subsequent) == -1)
		//	return (-1);
		if (check_redir(current_input, subsequent) == -1)
			return (-1);
		//{
		//	if (current_input->pipe_sign == 1)
		//		check_is_pipe();
		//	else
		//		check_no_pipe();
		//	if (current_input->temp_line == 1)
		//		check_is_line();
		//	else
		//		check_no_line();
		//	if (check_redir(current_input, subsequent) == -1)
		//		return (-1);
		//}
		current = current->next;
		i++;
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
		g_exitcode = 2;
		ft_error("Syntax error: how dare you? ", SYNTAX, 1);
		return (-1);
	}
	if (in1->pipe_sign == 1 && !ft_strncmp(in1->temp_line, "", 1) && in2->pipe_sign)
	{
		g_exitcode = 2;
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
			g_exitcode = 2;
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
			g_exitcode = 2;
			ft_error("Syntax error: Don't mess up with me, idiot!", SYNTAX, 1);
			return (-1);
		}
	}
	return (0);
}


	//if (!(line_lst->next))
	//	{
	//		if (((t_input *)line_lst->content)->pipe_sign == 1)
	//		{
	//			ft_error_minishell("Syntax error: parse error456.", SYNTAX, 2);
	//			return (-1);
	//		}
	//	}
		// 连续两个node为空，报错newline with prompt
		// if line not null, and if there is a pipe, still 2 more nodes,

		// 00 pipe = 1, line not empty,
		// 01 line not empty,
		// 02 line not empty


		// 00 pipe = 0,  line not empty
		// 01 line not empty

		//if (!ft_strncmp(((t_input *)line_lst->content)->temp_line, "", 1)) // handle error: parse error, '| |', '< >', '> <<'
		//{
		//	if (((t_input *)line_lst->content)->pipe_sign == 1)
		//	{
		//		if (line_lst->next->next && !ft_strncmp(((t_input *)line_lst->next->content)->temp_line, "", 1)
		//			&& !ft_strncmp(((t_input *)line_lst->next->next->content)->temp_line, "", 1))
		//			{
		//				ft_error_minishell("Syntax error: parse error123.", SYNTAX, 2);
		//				return (-1);
		//			}
		//	}
		//	else
		//	{
		//		if (line_lst->next && !ft_strncmp(((t_input *)line_lst->next->content)->temp_line, "", 1))
		//			{
		//				ft_error_minishell("Syntax error: parse error1.", SYNTAX, 2);
		//				return (-1);
		//			}
		//	}
		//}
