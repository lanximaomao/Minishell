#include "minishell.h"

/* 1. 先检查当前cmd segment的redirection，存入对应in/out file后，删除node，方便后续cmd组合；
 * 2. 检查是否是builtin函数；
 * 3. 将cmd组合成char **作为execve的第二个参数
 * 4. 将cmd_tokens存入cmd_lst的node中 */


void ft_error(char* msg)
{
	ft_printf("\033[1;31mError! \033[0m%s", msg);
	return ;
}

char *ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void *new_ptr = NULL;

	if (!new_size)
	{
		free(ptr);
		return NULL;
	}
	new_ptr = (void *)ft_calloc(new_size, sizeof(void));
	if (!new_ptr)
		return NULL;

	if (ptr != NULL)
	{
		ft_memcpy(new_ptr, ptr, old_size);
		free(ptr);
		ptr = NULL;
	}
	return new_ptr;
}

char **handle_heredoc(char *eof)
{
	int i = 0;
	int count = 0;
	char **heredoc;

	heredoc = (char **)ft_calloc(1, sizeof(char *)); // for (char **) terminated with NULL
	if (!heredoc)
		return (NULL);

	while(1)
	{
		heredoc = (char **)ft_realloc(heredoc, (count + 1) * sizeof(char *), (count + 2) * sizeof(char *)); // for the next readline;
		if (!heredoc)
		{
			ft_error("malloc error.\n");
			return (NULL);
		}
		heredoc[i] = readline("heredoc >> ");
		if (!heredoc[i])
		{
			free(heredoc);
			ft_error("readline error.\n");
			return (NULL);
		}
		count++;
		if (ft_strncmp(heredoc[i], eof, ft_strlen(heredoc[i])) == 0)
		{
			free(heredoc[i]);
			heredoc[i] = NULL;
			break;
		}
	}
	return (heredoc);
}

// input line_lst return tokens, in here, one token is one complete cmd
t_list *parse_tokens(t_list *line_lst)
{
	int i;
	int j;
	int fd = 0;
	t_list *cmd_lst = NULL;
	t_list *node = NULL;
	t_token *cmd_tokenss; // the single cmd split from line input


	cmd_tokens = (t_token *)malloc(sizeof(t_token));
	if (!cmd_tokens)
		return (NULL);

	while (line_lst)
	{
		i = 0;
		j = 0;
		while (((t_input *)line_lst->content)->pipe_sign != 1)
		{

			if (((t_input *)line_lst->content)->redir_sign == 1)
			{ // each redirection file cannot be empty, parse error
				cmd_tokens->infile[i++] = ft_strdup(((t_input *)line_lst->content)->next->temp_line);
			}
			if (((t_input *)line_lst->content)->redir_sign == 2)
			{
				// heredoc 新建一个临时文件，存入输入到数据，并将临时文件的路径保存在cmd_tokens->infile中
			}
			if (((t_input *)line_lst->content)->redir_sign == 3)
			{ // each redirection file cannot be empty, parse error
				cmd_tokens->outfile[j] = ft_strdup(((t_input *)line_lst->content)->next->temp_line);
				cmd_tokens->output_type[j++] = 1;
			}
			if (((t_input *)line_lst->content)->redir_sign == 4)
			{ // each redirection file cannot be empty, parse error
				cmd_tokens->outfile[j] = ft_strdup(((t_input *)line_lst->content)->next->temp_line);
				cmd_tokens->output_type[j++] = 2;
			}
			if (((t_input *)line_lst->content)->redir_sign == 5)
			{
				// error
				if (((t_input *)line_lst->content)->next->redir_sign == 1)
					cmd_tokens->errfile = ft_strdup(((t_input *)line_lst->content)->next->next->temp_line);
			}
			if (((t_input *)line_lst->content)->redir_sign == 6)
			{
				// heredoc不能作为输入，只能进行heredoc的使用
			}
			if (((t_input *)line_lst->content)->redir_sign == 7)
			{
				// heredoc不能作为输入，只能进行heredoc的使用
			}
			if (((t_input *)line_lst->content)->redir_sign == 8)
			{
				// heredoc不能作为输入，只能进行heredoc的使用
			}
			if (((t_input *)line_lst->content)->redir_sign == 9)
			{
				// heredoc不能作为输入，只能进行heredoc的使用
			}







			line_lst = line_lst->next;
		}
		node = ft_lstnew((t_token *)cmd_tokens);
		if (!node)
		{
			ft_printf("Malloc Failed.");
			return (NULL);
		}
		ft_lstadd_back(&cmd_lst, node);
		line_lst = line_lst->next;
	}

	return (cmd_tokens);
}




// < infile 'ls' "-l" | wc -l > outfile

