/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:22:00 by lliu              #+#    #+#             */
/*   Updated: 2023/07/31 16:04:26 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_input(t_input **input)
{
	*input = (t_input *)ft_calloc(sizeof(t_input), 1);
	if (!input)
		ft_error(" minishell: malloc fail", MALLOC, 0);
	(*input)->tmp_line = NULL;
	(*input)->quote_type = 0;
	(*input)->pipe_sign = 0;
	(*input)->redir_sign = 0;
}

/* check if the quote is closed or not */
static int	handle_quote(t_input *input, char *line, int i, int *len)
{
	int		count;
	char	quote;

	count = 1;
	quote = line[i];
	if (quote == '\'')
		input->quote_type = 1;
	else if (quote == '\"')
		input->quote_type = 2;
	while (line[++i] != quote)
	{
		if (!line[i])
		{
			ft_error("minishell: Syntax error: quote not closed", SYNTAX, 1);
			return (-1);
		}
		count++;
	}
	*len += count;
	return (i);
}

static int	handle_token(t_input *input, char *line, int i, int *len)
{
	*len = 0;
	while (line[i] != ' ' && line[i] && ++(*len))
	{
		if ((line[i] == '|' || line[i] == '<' || line[i] == '>'))
		{
			if (line[i] == '|')
				input->pipe_sign = 1;
			else if (line[i] == '<' && line[i + 1] != '<')
				input->redir_sign = 1;
			else if (line[i] == '<' && line[i + 1] == '<')
				input->redir_sign = 2;
			else if (line[i] == '>' && line[i + 1] != '>')
				input->redir_sign = 3;
			else if (line[i] == '>' && line[i + 1] == '>')
				input->redir_sign = 4;
			(*len)--;
			break ;
		}
		else if (line[i] == '\'' || line[i] == '\"')
			i = handle_quote(input, line, i, len);
		if (i == -1)
			return (-1);
		i++;
	}
	return (i);
}

static void	handle_input(t_input *input, int *i)
{
	if (input->redir_sign == 2 || input->redir_sign == 4)
		*i += 1;
	if (!ft_strncmp(input->tmp_line, "", 1) && (input->redir_sign
			|| input->pipe_sign))
		input->ignore_sign = 1;
}

t_list	*lexer_get_linelst(char *line, t_list *line_lst, int i)
{
	int		len;
	t_input	*input;

	while (line[++i])
	{
		if (!(line[i] == ' ' || (line[i] > 8 && line[i] < 14)))
		{
			init_input(&input);
			i = handle_token(input, line, i, &len);
			if (i == -1)
			{
				free_input(input);
				free_lst_content(line_lst, 0);
				return (NULL);
			}
			input->tmp_line = ft_substr(line, i - len, len);
			if (!input->tmp_line)
				ft_error(" minishell: malloc fail", MALLOC, 0);
			handle_input(input, &i);
			create_lst(&line_lst, (t_input *)input);
		}
		if (!line[i])
			break ;
	}
	return (line_lst);
}
