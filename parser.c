/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srall <srall@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 00:45:46 by srall             #+#    #+#             */
/*   Updated: 2023/05/16 02:57:47 by srall            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signal.h"

void init_tokens(t_token *tokens, int num_cmd)
{
	tokens->cmd = NULL;
	tokens->args = NULL;
	tokens->infile = NULL;
	tokens->outfile = NULL;
	tokens->output_type = NULL;
	tokens->cmd_id = num_cmd;
	tokens->num_args = 0;
	tokens->num_infile = 0;
	tokens->num_outfile_type = 0;
	//tokens->fd_in = 0;
	//tokens->fd_out = 1;
	tokens->fd_in = dup(0);
	tokens->fd_out = dup(1);
}

// function: store the heredoc into a tem_heredoc_file(1st argument) line by line followed a newline
// return: -1 means error and handle this, no more free in this function
// after call: 	delete the tmp_heredoc_file after this cmd_node, and strongly recommend to use different file_name for 1st argument
// 				<< heredoc 需要将每行都要执行参数扩展、命令替换以及算术扩展
void handle_heredoc(t_list *env_lst, t_input *input, int exitcode, char *num_heredoc)
{
	int fd; // for tmp_file, store the heredoc
	char *heredoc;
	char *line;
	char *file_name;

	file_name = ft_strjoin("heredoc_name", num_heredoc);
	if ((fd = open(file_name, O_WRONLY|O_CREAT|O_TRUNC, 0644)) < 0) // 读写/读/读
		ft_error_minishell("Open heredoc_name failed", FILE_OP, 1); // Pls remember free_str(file_name);!!!!!
	free_str(file_name);
	while(g_exitcode != 256)
	{
		signal_handler_heredoc();
		line = readline("heredoc >> ");
		if (!line && !errno) // 相当于SIGTERM
		{
			close(fd);
			g_exitcode = 0;
			return ;
		}
		if (!ft_strncmp(line, input->temp_line, ft_strlen(input->temp_line))
			&& ft_strlen(input->temp_line) == ft_strlen(line) && free_str(line))
			break;
		else
		{ // expand the $(...)
			if (ft_strchr(line, '$') && !input->quote_type)
				line = replace_env_expand(line, env_lst);
			if (!(heredoc = ft_strjoin(line, "\n"))) // line no need free
				ft_error_minishell("Malloc failed", MALLOC, 2);
			if (write(fd, heredoc, ft_strlen(heredoc)) == -1)
				ft_error_minishell("Open heredoc_name failed", FILE_OP, 1);
			free_str(heredoc);
		}
	}
	g_exitcode = 1;
	close(fd);
}

// parse < << input redirection,
void parse_redir12(t_token *cmd_tokens, t_list *line_lst, t_list *env_lst, int i, int exitcode)
{
	char *num_heredoc;

	if (((t_input *)line_lst->content)->redir_sign == 1) // <
	{
		if (!cmd_tokens->infile)
		{
			if (!(cmd_tokens->infile = (char **)ft_calloc(sizeof(char *), 1)))
				ft_error_minishell("Malloc failed", MALLOC, 2);
		}
		else
			cmd_tokens->infile = (char **)ft_realloc(cmd_tokens->infile, sizeof(char *) * (i + 1), sizeof(char *) * (i + 2));
		cmd_tokens->infile[i] = ft_strdup(((t_input *)line_lst->next->content)->temp_line);
		if (!cmd_tokens->infile[i])
			ft_error_minishell("Malloc failed", MALLOC, 2);
	}
	else if (((t_input *)line_lst->content)->redir_sign == 2) // <<
	{
		num_heredoc = ft_itoa(cmd_tokens->cmd_id);
		handle_heredoc(env_lst, ((t_input *)line_lst->next->content), exitcode, num_heredoc);
		cmd_tokens->infile = (char **)ft_realloc(cmd_tokens->infile, sizeof(char *) * (i + 1), sizeof(char *) * (i + 2));
		cmd_tokens->infile[i] = ft_strjoin("heredoc_name", num_heredoc); // tmp_file_name same with in handle_heredoc
		if (!cmd_tokens->infile[i])
			ft_error_minishell("Malloc failed", MALLOC, 2);
		free_str(num_heredoc);
	}
	cmd_tokens->num_infile = ++i;
}

// parse > >> output redirection
void parse_redir34(t_token *cmd_tokens, t_input *input, int redir_sign, int i)
{
	if (!cmd_tokens->outfile)
	{
		if (!(cmd_tokens->outfile = (char **)ft_calloc(sizeof(char *), 1)))
			ft_error_minishell("Malloc failed", MALLOC, 2);
	}
	else
		cmd_tokens->outfile = (char **)ft_realloc(cmd_tokens->outfile, sizeof(char *) * (i + 1), sizeof(char *) * (i + 2));
	cmd_tokens->outfile[i] = ft_strdup(input->temp_line);
	if (!cmd_tokens->outfile[i])
		ft_error_minishell("Malloc failed", MALLOC, 2);
	if (!cmd_tokens->output_type)
	{
		if (!(cmd_tokens->output_type = (int *)ft_calloc(sizeof(int), 1)))
			ft_error_minishell("Malloc failed", MALLOC, 2);
	}
	else
		cmd_tokens->output_type = (int *)ft_realloc(cmd_tokens->output_type, sizeof(int) * (i + 1), sizeof(int) * (i + 2));
	if (redir_sign == 3)
		cmd_tokens->output_type[i] = 1;
	else if (redir_sign == 4)
		cmd_tokens->output_type[i] = 2;
	cmd_tokens->num_outfile_type = ++i;
}

void parse_cmd_args(t_token *cmd_tokens, t_input *input, int *k)
{
	if (!cmd_tokens->cmd) // cmd
	{
		if (!(cmd_tokens->cmd = ft_strdup(input->temp_line)))
			ft_error_minishell("Malloc failed", MALLOC, 2);
	}
	if (!cmd_tokens->args) // add the cmd in front of args
	{
		if (!(cmd_tokens->args = (char **)ft_calloc(sizeof(char *), 2)))
			ft_error_minishell("Malloc failed", MALLOC, 2);
	}
	else
		cmd_tokens->args = (char **)ft_realloc(cmd_tokens->args, sizeof(char *) * (*k + 1), sizeof(char *) * (*k + 2));
	cmd_tokens->args[*k] = ft_strdup(input->temp_line);
	if (!cmd_tokens->args[*k])
		ft_error_minishell("Malloc failed", MALLOC, 2);
	*k += 1;
	cmd_tokens->num_args = *k;
}

// each cmd is a cmd_lst node, iterate the line_lst until | as one cmd
t_list *iterate_cmds(t_token *cmd_tokens, t_list *line_lst, t_list *env_lst, int exitcode, int *k)
{
	int i;
	int j;

	i = 0; // for num_infile
	j = 0; // for num_outfile
	while (line_lst)
	{ // no handle the <>/<>>/></><</<<>/<<>>/>></>><</>>>/>>>>, should be syntax error or
		if (((t_input *)line_lst->content)->redir_sign != 0)
		{
			if (line_lst->next == NULL) // handle error: each redirection file cannot be empty, parse error
				ft_error_minishell("Syntax error: no redirection argument.", SYNTAX, 2);
			if (((t_input *)line_lst->content)->redir_sign == 1
				|| ((t_input *)line_lst->content)->redir_sign == 2) // < >
				parse_redir12(cmd_tokens, line_lst, env_lst, i++, exitcode);
			else if (((t_input *)line_lst->content)->redir_sign == 3
				|| ((t_input *)line_lst->content)->redir_sign == 4) // >> <<
				parse_redir34(cmd_tokens, ((t_input *)line_lst->next->content), ((t_input *)line_lst->content)->redir_sign, j++);
			line_lst = line_lst->next;
		}
		else if (ft_strncmp(((t_input *)line_lst->content)->temp_line, "", 1))
			parse_cmd_args(cmd_tokens, ((t_input *)line_lst->content), k);
		if (((t_input *)line_lst->content)->pipe_sign == 1)
			break;
		line_lst = line_lst->next;
	}
	return line_lst;
}

// function: input line_lst return tokens, in here, one token is one complete cmd
// return: null means error and handle this;
// leaks: handled the error free
// after call: free the cmd_lst, free the line_lst from the get_linelst() in lexer.c
t_list *parse_cmds(t_list *line_lst, t_list *env_lst, int exitcode)
{
	int num_cmd;
	int k;
	t_list *node;
	t_list *cmd_lst;
	t_token *cmd_tokens; // the single cmd split from line input

	num_cmd = 0;
	node = NULL;
	cmd_lst = NULL;
	cmd_tokens = NULL;
	while (line_lst)
	{
		k = 0; // for num_args, k = 0 for cmd in front of args
		if (!(cmd_tokens = (t_token *)ft_calloc(sizeof(t_token), 1)))
			ft_error_minishell("Malloc failed", MALLOC, 2);
		init_tokens(cmd_tokens, num_cmd);
		line_lst = iterate_cmds(cmd_tokens, line_lst, env_lst, exitcode, &k);
		node = ft_lstnew((t_token *)cmd_tokens);
		if (!node)
			ft_error_minishell("Malloc failed", MALLOC, 2);
		ft_lstadd_back(&cmd_lst, node);
		if (!line_lst) // 上面的redir会向下遍历一位，所以在这里判断一下是否最后，以防止segfault
			break;
		num_cmd++;
		line_lst = line_lst->next;
	}
	return (cmd_lst);
}


