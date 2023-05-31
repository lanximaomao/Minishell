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
	t_list	*n1;
	t_list	*n2;
	t_list	*n3;
	t_input	*in1;
	t_input	*in2;
	t_input	*in3;

	i = 1;
	n1 = line_lst;
	n2 = NULL;
	n3 = NULL;
	in1 = NULL;
	in2 = NULL;
	in3 = NULL;

	while (n1)
	{
		in1 = (t_input *)(n1->content);

		//printf("cmd=%d, line=%s\n", i, in1->temp_line);
		//printf("cmd=%d, pipe=%d\n", i, in1->pipe_sign);
		//printf("cmd=%d, redir=%d\n\n", i, in1->redir_sign);

		n2 = n1->next;

		// | pwd
		if ( i == 1 && in1->pipe_sign == 1 && !ft_strncmp(in1->temp_line, "", 1))
		{
			ft_error("pipe at beginning. ", SYNTAX, 1);
			return (-1);
		}
		if (n2)
		{
			n3 = n2->next;
			in2 = (t_input *)(n2->content);
			if (in1->pipe_sign == 1 && !ft_strncmp(in2->temp_line, "", 1))
			{
				if (!n3)
				{
					ft_error("Syntax: pipe before cmd.", SYNTAX, 1);
					return(-1);
				}
			}
			if (in1->redir_sign != 0 && in2->redir_sign != 0 && ft_strncmp(in2->temp_line, "", 1) == 0)
			{
				ft_error("Two redirection in a row. ", SYNTAX, 1);
				return(-1);
			}
		}
		else
		{
			if (in1->pipe_sign == 1)
			{
				ft_error("Syntax: pipe. ", SYNTAX, 1);
				return(-1);
			}
			if (in1->redir_sign != 0 && in2 == NULL)
			{
				ft_error("one redirection in a end. ", SYNTAX, 1);
				return(-1);
			}
		}
		if (n3)
		{
			in3 = (t_input *)(n3->content);
		}
		if (!ft_strncmp(in1->temp_line, "", 1)) // handle error: parse error, '| |', '< >', '> <<'
		{
			if (in1->pipe_sign == 1)
			{
				if (n3 && !ft_strncmp(in2->temp_line, "", 1)
					&& !ft_strncmp(in3->temp_line, "", 1))
					{
						ft_error("Syntax: double.", SYNTAX, 1);
						return (-1);
					}
			}
			else
			{
				if (n1 && !ft_strncmp(in2->temp_line, "", 1))
					{
						ft_error("Syntax error: parsing", SYNTAX, 1);
						return (-1);
					}
			}
		}
		n1 = n1->next;
		i++;
	}
	return (0);
}


/*
** error 1 covers cases like: | or ls |
** error 2 covers cases like: | pwd
*/
int	check_pipe(t_input *in1, t_input *in2, t_list *n1)

{
	if (in1->pipe_sign == 1 && n1 == NULL)
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
int	check_double(t_input *in1, t_input *in2, t_list *n1)
{
	if (ft_strncmp(in1->temp_line, "", 1) == 0)
	{
		if (n1 && ft_strncmp(in2->temp_line, "", 1) == 0)
		{
			g_exitcode = 2;
			ft_error("Syntax error: Aren't you an idiot? ", SYNTAX, 1);
			return (-1);
		}
	}
	return (0);
}

/* error redirection if no filename is found after redirection sign */
int	check_redir(t_input *in1, t_list *n1)
{
	if (in1->redir_sign != 0)
	{
		if (n1 == NULL)
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
	//		if (in1->pipe_sign == 1)
	//		{
	//			ft_error_minishell("Syntax error: parse error456.", SYNTAX, 2);
	//			return (-1);
	//		}
	//	}
	//	// 连续两个node为空，报错newline with prompt
	//	// if line not null, and if there is a pipe, still 2 more nodes,

	//	// 00 pipe = 1, line not empty,
	//	// 01 line not empty,
	//	// 02 line not empty


	//	// 00 pipe = 0,  line not empty
	//	// 01 line not empty

	//	if (!ft_strncmp(in1->temp_line, "", 1)) // handle error: parse error, '| |', '< >', '> <<'
	//	{
	//		if (in1->pipe_sign == 1)
	//		{
	//			if (n3 && !ft_strncmp(in2->temp_line, "", 1)
	//				&& !ft_strncmp(((t_input *)n3->content)->temp_line, "", 1))
	//				{
	//					ft_error_minishell("Syntax error: parse error123.", SYNTAX, 2);
	//					return (-1);
	//				}
	//		}
	//		else
	//		{
	//			if (line_lst->next && !ft_strncmp(in2->temp_line, "", 1))
	//				{
	//					ft_error_minishell("Syntax error: parse error1.", SYNTAX, 2);
	//					return (-1);
	//				}
	//		}
	//	}
