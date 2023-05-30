#include "minishell.h"
#include "validator.h"

// part of code is from handle_args_expand

// ! check for unclosed quotes is in lexer

//check for unclosed pipe
//check for incomplete redir
// to be add: <f1>
// segfault: << f1 >


int	validator(t_list *line_lst)
{
	t_list	*current;
	t_list	*subsequent;
	t_input	*current_input;
	t_input	*subsequent_input;

	current = line_lst;
	while (current)
	{
		subsequent = current->next;
		current_input = (t_input *)(current->content);
		printf("line=%s", current_input->temp_line);
		if (current_input->temp_line == NULL)
			printf(" !NULL LINE\n");
		else
			printf(" !NOT NULL\n");
		printf("pipe=%d\n", current_input->pipe_sign);
		printf("redir=%d\n", current_input->redir_sign);
		//printf("quote=%d\n", current_input->quote_type);
		if (subsequent)
		{
			subsequent_input = (t_input *)(subsequent->content);
			printf("sub_line=%s", subsequent_input->temp_line);
			if (current_input->temp_line == NULL)
				printf(" !NULL LINE\n");
			else
				printf(" !NOT NULL\n");
			printf("sub_pipe=%d\n", subsequent_input->pipe_sign);
			printf("sub_redir=%d\n", subsequent_input->redir_sign);
			//printf("quote=%d\n", current_input->quote_type);
		}
		if (current_input->quote_type == 0)
		{
			if (check_pipe(current_input, subsequent_input, subsequent) == -1)
				return (-1);
			if (subsequent && check_double(current_input, subsequent_input, subsequent) == -1)
				return (-1);
			if (check_redir(current_input, subsequent) == -1)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}

//quote
int	check_pipe(t_input *in1, t_input *in2, t_list *subsequent) // to cover | or ls|
{
	if (in1->pipe_sign == 1 && subsequent == NULL)
	{
		ft_error("Syntax error 01-1", SYNTAX, 1);
		return (-1);
	}
	if (in1->pipe_sign == 1 && ft_strncmp(in1->temp_line, "", 1) == 0)// to cover |pwd
	{
		ft_error("Syntax error 01-2", SYNTAX, 1);
		return (-1);
	}
	return (0);
}

//02: <>, ||,
// ls|pwd|
int	check_double(t_input *in1, t_input *in2, t_list *subsequent)
{
	if (ft_strncmp(in1->temp_line, "", 1) == 0)
	{
		if (subsequent && ft_strncmp(in2->temp_line, "", 1) == 0) // to cover ls <> pwd
		{
			ft_error("Syntax error 02-1", SYNTAX, 1);
			return (-1);
		}
	}
	return (0);
}

// error if no filename is found after redirection sign//
int	check_redir(t_input *in1, t_list *subsequent)//
{
	if (in1->redir_sign != 0)//
	{
		if (subsequent == NULL)
		{
			ft_error("Syntax error 04", SYNTAX, 1); // > or < or << or >> or < >
			return (-1);
		}
	}
	return (0);
}
