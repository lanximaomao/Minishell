#include "minishell.h"

/* 1. 先检查当前cmd segment的redirection，存入对应in/out file后，删除node，方便后续cmd组合；
 * 2. 检查是否是builtin函数；
 * 3. 将cmd组合成char **作为execve的第二个参数
 * 4. 将cmd_tokens存入cmd_lst的node中 */


// function: store the heredoc into a tem_heredoc_file(1st argument) line by line followed a newline
// return: -1 means error and handle this, no more free in this function
// after call: 	delete the tmp_heredoc_file after this cmd_node, and strongly recommend to use different file_name for 1st argument
// 				<< heredoc 需要将每行都要执行参数扩展、命令替换以及算术扩展
int handle_heredoc(char *tmp_file_name, char *eof)
{
	int fd = 0; // for tmp_file, store the heredoc
	char *heredoc = NULL;
	char *line = NULL;

	while(1)
	{
		if (!(line = readline("heredoc >> ")))
		{
			perror("Readline error.\n");
			return (-1);
		}
		if (ft_strncmp(line, eof, ft_strlen(line)) == 0)
		{
			free(line);
			break;
		}
		if (!(heredoc = ft_strjoin(line, "\n")))
		{
			free(line);
			perror("Malloc error.\n");
			return (-1);
		}
		if (!fd && (fd = open(tmp_file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0) // 读写/读/读
		{
			free(heredoc);
			perror("Open infile failed!\n");
			return (-1);
		}
		if (write(fd, heredoc, ft_strlen(heredoc)) == -1)
		{
			free(heredoc);
			perror("Write infile failed!\n");
			return (-1);
		}
		free(heredoc);
		heredoc = NULL;
	}
	close(fd);
	return (1);
}

// function: input line_lst return tokens, in here, one token is one complete cmd
// return: null means error and handle this;
// leaks: handled the error free
// after call: free the cmd_lst, free the line_lst from the get_linelst() in lexer.c
t_list *parse_cmds(t_list *line_lst)
{
	int i;
	int j;
	int k;
	int error_return = 0;
	int fd = 0;
	t_list *cmd_lst = NULL;
	t_list *node = NULL;
	t_token *cmd_tokens; // the single cmd split from line input

	if (!line_lst)
		return (NULL);

	while (line_lst)
	{
		i = 0; // for num_infile
		j = 0; // for num_outfile
		k = 0; // for num_args
		cmd_tokens = (t_token *)ft_calloc(sizeof(t_token), 1);
		if (!cmd_tokens)
			return (NULL);
		init_token(cmd_tokens);
		while (line_lst && ((t_input *)line_lst->content)->pipe_sign != 1)
		{ // no handle the <>/<>>/></><</<<>/<<>>/>></>><</>>>/>>>>, should be syntax error or
			// line_lst->next一次我就需要扩展一次，否则得记录很多expand_sign
			// if (((t_input *)line_lst->content)->quote_type == 2)
			// 	handle_expand(((t_input *)line_lst->content)->temp_line);
			if (((t_input *)line_lst->content)->redir_sign != 0)
			{
				if (((t_input *)line_lst->content)->redir_sign == 1) // <
				{ // each redirection file cannot be empty, parse error
					// maclloc in here
					if (!cmd_tokens->infile)
					{
						cmd_tokens->infile = (char **)ft_calloc(sizeof(char *), 1);
						if (!cmd_tokens->infile)
						{
							perror("Malloc error.\n");
							free_token(cmd_tokens, i, j, k);
							return (NULL);
						}
					}
					else
						cmd_tokens->infile = (char **)ft_realloc(cmd_tokens->infile, sizeof(char *) * (i + 1), sizeof(char *) * (i + 2));
					cmd_tokens->infile[i] = ft_strdup(((t_input *)line_lst->next->content)->temp_line);
					if (!cmd_tokens->infile[i])
					{
						perror("Malloc error.\n");
						free_token(cmd_tokens, i, j, k);
						return (NULL);
					}
					i++;
					cmd_tokens->num_infile = i;
				}
				else if (((t_input *)line_lst->content)->redir_sign == 2) // <<
				{
					// heredoc 新建一个临时文件，存入输入到数据，并将临时文件的路径保存在cmd_tokens->infile中
					// delete the heredoc tmp_file after used
					error_return = handle_heredoc("tmp_file_name", ((t_input *)line_lst->next->content)->temp_line);
					if (error_return == -1)
						return (NULL);
					cmd_tokens->infile[i] = ft_strdup("tmp_file_name");
					if (!cmd_tokens->infile[i])
					{
						perror("Malloc error.\n");
						free_token(cmd_tokens, i, j, k);
						return (NULL);
					}
					i++;
					cmd_tokens->num_infile = i;
				}
				else if (((t_input *)line_lst->content)->redir_sign == 3) // >
				{ // each redirection file cannot be empty, parse error
					if (!cmd_tokens->outfile)
					{
						cmd_tokens->outfile = (char **)ft_calloc(sizeof(char *), 1);
						if (!cmd_tokens->outfile)
						{
							perror("Malloc error.\n");
							free_token(cmd_tokens, i, j, k);
							return (NULL);
						}
					}
					else
						cmd_tokens->outfile = (char **)ft_realloc(cmd_tokens->outfile, sizeof(char *) * (j + 1), sizeof(char *) * (j + 2));
					cmd_tokens->outfile[j] = ft_strdup(((t_input *)line_lst->next->content)->temp_line);
					if (!cmd_tokens->outfile[j])
					{
						perror("Malloc error.\n");
						free_token(cmd_tokens, i, j, k);
						return (NULL);
					}
					if (!cmd_tokens->output_type)
					{
						cmd_tokens->output_type = (int *)ft_calloc(sizeof(int), 1);
						if (!cmd_tokens->output_type)
						{
							perror("Malloc error.\n");
							free_token(cmd_tokens, i, j, k);
							return (NULL);
						}
					}
					else
						cmd_tokens->output_type = (int *)ft_realloc(cmd_tokens->output_type, sizeof(int) * (j + 1), sizeof(int) * (j + 2));
					cmd_tokens->output_type[j] = 1;
					j++;
					cmd_tokens->num_outfile_type = j;
				}
				else if (((t_input *)line_lst->content)->redir_sign == 4) // >>
				{ // each redirection file cannot be empty, parse error
					if (!cmd_tokens->outfile)
					{
						cmd_tokens->outfile = (char **)ft_calloc(sizeof(char *), 1);
						if (!cmd_tokens->outfile)
						{
							perror("Malloc error.\n");
							free_token(cmd_tokens, i, j, k);
							return (NULL);
						}
					}
					else
						cmd_tokens->outfile = (char **)ft_realloc(cmd_tokens->outfile, sizeof(char *) * (j + 1), sizeof(char *) * (j + 2));
					cmd_tokens->outfile[j] = ft_strdup(((t_input *)line_lst->next->content)->temp_line);
					if (!cmd_tokens->outfile[j])
					{
						perror("Malloc error.\n");
						free_token(cmd_tokens, i, j, k);
						return (NULL);
					}
					cmd_tokens->output_type[j] = 2;
					j++;
					cmd_tokens->num_outfile_type = j;
				}
				line_lst = line_lst->next;
				// if (((t_input *)line_lst->content)->quote_type == 2)
				// 	handle_expand(((t_input *)line_lst->content)->temp_line);
			}
			else if (!cmd_tokens->cmd) // cmd
			{
				cmd_tokens->cmd = ft_strdup(((t_input *)line_lst->content)->temp_line);
				if (!cmd_tokens->cmd)
				{
					perror("Malloc error.\n");
					free_token(cmd_tokens, i, j, k);
					return (NULL);
				}
			}
			else // args
			{
				if (!cmd_tokens->args)
				{
					cmd_tokens->args = (char **)ft_calloc(sizeof(char *), 1);
					if (!cmd_tokens->args)
					{
						perror("Malloc error.\n");
						free_token(cmd_tokens, i, j, k);
						return (NULL);
					}
				}
				else
					cmd_tokens->args = (char **)ft_realloc(cmd_tokens->args, sizeof(char *) * (k + 1), sizeof(char *) * (k + 2));
				cmd_tokens->args[k] = ft_strdup(((t_input *)line_lst->content)->temp_line);
				if (!cmd_tokens->args[k])
				{
					perror("Malloc error.\n");
					free_token(cmd_tokens, i, j, k);
					return (NULL);
				}
				k++;
				cmd_tokens->num_args = k;
			}
			line_lst = line_lst->next;
		}
		node = ft_lstnew((t_token *)cmd_tokens);
		if (!node)
		{
			perror("Malloc Failed.");
			free_token(cmd_tokens, i, j, k);
			return (NULL);
		}
		ft_lstadd_back(&cmd_lst, node);
		if (!line_lst)
			break;
		line_lst = line_lst->next;
	}
	return (cmd_lst);
}

/*
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
			printf("num_args: %d\n", ((t_token *)cmd_lst->content)->num_args);
			printf("num_infile: %d\n", ((t_token *)cmd_lst->content)->num_infile);
			printf("num_outfile_type: %d\n", ((t_token *)cmd_lst->content)->num_outfile_type);
			printf("expand_sign: %d\n", ((t_token *)cmd_lst->content)->expander_sign);
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



// < infile 'ls' "-l" | wc -l > outfile
// <infile grep test | wc -l >outfile

// malloc, free, write, close, fork, waitpid, signal, kill, exit, chdir, execve, dup, dup2, pipe, strcmp, strncmp
// <<追加到outfile的时候，后面带有\n

// 注意，在bash中和zsh的区别：
// 1. <infile <<eof <outfile grep "bash" 只考虑最后一个input；
// 2.  ls -l | grep 16 > infile >> outfile 只考虑最后一个output；但是<会覆盖前面的 outfile, <<不追加
// 3.  ls -l | grep 16 2> infile 2>> outfile 只考虑最后一个output；但是<会覆盖前面的 outfile，<<不追加

