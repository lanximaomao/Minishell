/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srall <srall@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 00:45:46 by srall             #+#    #+#             */
/*   Updated: 2023/04/21 17:26:30 by srall            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 1. 先检查当前cmd segment的redirection，存入对应in/out file后，删除node，方便后续cmd组合；
 * 2. 检查是否是builtin函数；
 * 3. 将cmd组合成char **作为execve的第二个参数
 * 4. 将cmd_tokens存入cmd_lst的node中 */

void init_tokens(t_token *tokens)
{
	tokens->cmd = NULL;
	tokens->args = NULL;
	tokens->infile = NULL;
	tokens->outfile = NULL;
	tokens->output_type = NULL;
	tokens->num_args = 0;
	tokens->num_infile = 0;
	tokens->num_outfile_type = 0;
}

// function: store the heredoc into a tem_heredoc_file(1st argument) line by line followed a newline
// return: -1 means error and handle this, no more free in this function
// after call: 	delete the tmp_heredoc_file after this cmd_node, and strongly recommend to use different file_name for 1st argument
// 				<< heredoc 需要将每行都要执行参数扩展、命令替换以及算术扩展
void handle_heredoc(t_list *env_lst, t_input *input, int exitcode)
{
	int fd; // for tmp_file, store the heredoc
	char *heredoc;
	char *line;

	if ((fd = open("tmp_file_name", O_WRONLY|O_CREAT|O_TRUNC, 0644)) < 0) // 读写/读/读
		ft_error("Open tmp_file failed", FILE_OP);
	while(1)
	{
		if (!(line = readline("heredoc >> ")))
			ft_error("Readline failed", FUNC);
		if (!ft_strncmp(line, input->temp_line, ft_strlen(input->temp_line))
			&& ft_strlen(input->temp_line) == ft_strlen(line) && free_str(line))
			break;
		else
		{ // expand the $(...)
			if (ft_strchr(line, '$') && !input->quote_type)
				line = replace_env_expand(line, env_lst, exitcode);
			if (!(heredoc = ft_strjoin(line, "\n"))) // line no need free
				ft_error("Malloc failed", MALLOC);
			if (write(fd, heredoc, ft_strlen(heredoc)) == -1)
				ft_error("Open tmp_file failed", FILE_OP);
			free_str(heredoc);
		}
	}
	close(fd);
}

void parse_redir12(t_token *cmd_tokens, t_list *line_lst, t_list *env_lst, int i, int exitcode)
{
	if (((t_input *)line_lst->content)->redir_sign == 1)
	{
		if (!cmd_tokens->infile)
		{
			if (!(cmd_tokens->infile = (char **)ft_calloc(sizeof(char *), 1)))
				ft_error("Malloc failed", MALLOC);
		}
		else
			cmd_tokens->infile = (char **)ft_realloc(cmd_tokens->infile, sizeof(char *) * (i + 1), sizeof(char *) * (i + 2));
		cmd_tokens->infile[i] = ft_strdup(((t_input *)line_lst->next->content)->temp_line);
		if (!cmd_tokens->infile[i])
			ft_error("Malloc failed", MALLOC);
	}
	else if (((t_input *)line_lst->content)->redir_sign == 2)
	{
		handle_heredoc(env_lst, ((t_input *)line_lst->next->content), exitcode);
		cmd_tokens->infile = (char **)ft_realloc(cmd_tokens->infile, sizeof(char *) * (i + 1), sizeof(char *) * (i + 2));
		cmd_tokens->infile[i] = ft_strdup("tmp_file_name"); // tmp_file_name same with in handle_heredoc
		if (!cmd_tokens->infile[i])
			ft_error("Malloc failed", MALLOC);
	}
	cmd_tokens->num_infile = ++i;
}

void parse_redir34(t_token *cmd_tokens, t_input *input, int redir_sign, int i)
{
	if (!cmd_tokens->outfile)
	{
		if (!(cmd_tokens->outfile = (char **)ft_calloc(sizeof(char *), 1)))
			ft_error("Malloc failed", MALLOC);
	}
	else
		cmd_tokens->outfile = (char **)ft_realloc(cmd_tokens->outfile, sizeof(char *) * (i + 1), sizeof(char *) * (i + 2));
	cmd_tokens->outfile[i] = ft_strdup(input->temp_line);
	if (!cmd_tokens->outfile[i])
		ft_error("Malloc failed", MALLOC);
	if (!cmd_tokens->output_type)
	{
		if (!(cmd_tokens->output_type = (int *)ft_calloc(sizeof(int), 1)))
			ft_error("Malloc failed", MALLOC);
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
			ft_error("Malloc failed", MALLOC);
	}
	else // args
	{
		if (!cmd_tokens->args)
		{
			if (!(cmd_tokens->args = (char **)ft_calloc(sizeof(char *), 2)))
				ft_error("Malloc failed", MALLOC);
			if (!(cmd_tokens->args[0] = ft_strdup(cmd_tokens->cmd))) // add the cmd in front of args
				ft_error("Malloc failed", MALLOC);
		}
		else
			cmd_tokens->args = (char **)ft_realloc(cmd_tokens->args, sizeof(char *) * (*k + 1), sizeof(char *) * (*k + 2));
		cmd_tokens->args[*k] = ft_strdup(input->temp_line);
		if (!cmd_tokens->args[*k])
			ft_error("Malloc failed", MALLOC);
		*k += 1;
	}
	cmd_tokens->num_args = *k;
}

t_list *iterate_cmds(t_token *cmd_tokens, t_list *line_lst, t_list *env_lst, int exitcode, int *k)
{
	int i;
	int j;

	i = 0; // for num_infile
	j = 0; // for num_outfile
	while (line_lst && ((t_input *)line_lst->content)->pipe_sign != 1)
	{ // no handle the <>/<>>/></><</<<>/<<>>/>></>><</>>>/>>>>, should be syntax error or
		if (((t_input *)line_lst->content)->redir_sign != 0)
		{
			if (line_lst->next == NULL) // each redirection file cannot be empty, parse error
				ft_error("Syntax error", SYNTAX);
			if (((t_input *)line_lst->content)->redir_sign == 1
				|| ((t_input *)line_lst->content)->redir_sign == 2) // < >
				parse_redir12(cmd_tokens, line_lst, env_lst, i++, exitcode);
			else if (((t_input *)line_lst->content)->redir_sign == 3
				|| ((t_input *)line_lst->content)->redir_sign == 4) // >> <<
				parse_redir34(cmd_tokens, ((t_input *)line_lst->next->content), ((t_input *)line_lst->content)->redir_sign, j++);
			line_lst = line_lst->next;
		}
		else
			parse_cmd_args(cmd_tokens, ((t_input *)line_lst->content), k);
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
	int k;
	t_list *node;
	t_list *cmd_lst;
	t_token *cmd_tokens; // the single cmd split from line input

	node = NULL;
	cmd_lst = NULL;
	cmd_tokens = NULL;
	while (line_lst)
	{
		k = 1; // for num_args, k = 0 for cmd in front of args
		if (!(cmd_tokens = (t_token *)ft_calloc(sizeof(t_token), 1)))
			ft_error("Malloc failed", MALLOC);
		init_tokens(cmd_tokens);
		line_lst = iterate_cmds(cmd_tokens, line_lst, env_lst, exitcode, &k);
		node = ft_lstnew((t_token *)cmd_tokens);
		if (!node)
			ft_error("Malloc failed", MALLOC);
		ft_lstadd_back(&cmd_lst, node);
		if (!line_lst) // 上面的redir会向下遍历一位，所以在这里判断一下是否最后，以防止segfault
			break;
		line_lst = line_lst->next;
	}
	return (cmd_lst);
}

/* // test main function for parser
int main(int argc, char **argv)
{
	t_list *line_lst = NULL;
	t_input *input;
	char *line;
	t_list *cmd_lst = NULL;

	while (1)
	{
		line = readline("minishell\033[31m$\033[0;39m ");
		add_history(line);

		line_lst = get_linelst(line);
		// while (line_lst)
		// {
		// 	printf("%s\n", ((t_input *)line_lst->content)->temp_line);
		// 	printf("%d\n", ((t_input *)line_lst->content)->redir_sign);
		// 	printf("%d\n", ((t_input *)line_lst->content)->pipe_sign);
		// 	printf("%d\n", ((t_input *)line_lst->content)->quote_type);
		// 	line_lst = line_lst->next;
		// }
		if (!line_lst)
			printf("test1\n");
		cmd_lst = parse_cmds(line_lst);
		if (!cmd_lst)
			printf("test2\n");
		ft_lstfree(line_lst);
		while (cmd_lst)
		{
			printf("cmd: %s\n", ((t_token *)cmd_lst->content)->cmd);
			// printf("%s\n", ((t_token *)cmd_lst->content)->args[0]);
			// printf("%s\n", ((t_token *)cmd_lst->content)->infile[0]);
			// printf("%s\n", ((t_token *)cmd_lst->content)->outfile[0]);
			// printf("%d\n", ((t_token *)cmd_lst->content)->output_type[0]);
			// printf("num_args: %d\n", ((t_token *)cmd_lst->content)->num_args);
			// printf("num_infile: %d\n", ((t_token *)cmd_lst->content)->num_infile);
			// printf("num_outfile_type: %d\n", ((t_token *)cmd_lst->content)->num_outfile_type);
			// printf("expand_sign: %d\n", ((t_token *)cmd_lst->content)->expander_sign);
			cmd_lst = cmd_lst->next;
		}
		if (ft_strncmp(line, "exit", 4) == 0)
		{
			free(line);
			break ;
		}
	}
	return (0);
} */



// < infile 'ls' "-l" |wc -l > outfile
// <infile grep test | wc -l >outfile

// malloc, free, write, close, fork, waitpid, signal, kill, exit, chdir, execve, dup, dup2, pipe, strcmp, strncmp
// <<追加到outfile的时候，后面带有\n

// 注意，在bash中和zsh的区别：
// 1. <infile <<eof <outfile grep "bash" 只考虑最后一个input；
// 2.  ls -l | grep 16 > infile >> outfile 只考虑最后一个output；但是<会覆盖前面的 outfile, <<不追加
// 3.  ls -l | grep 16 2> infile 2>> outfile 只考虑最后一个output；但是<会覆盖前面的 outfile，<<不追加

