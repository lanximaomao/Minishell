#include "minishell.h"

void malloc_redir(t_token **cmd_tokens, int i)
{
	if (i == 0)
	{
		(*cmd_tokens)->file_redir = (char **)ft_calloc(sizeof(char *), 2);
		if (!(*cmd_tokens)->file_redir)
			ft_error("Malloc failed", MALLOC, 0);
		(*cmd_tokens)->file_redir[1] = NULL;
		(*cmd_tokens)->file_type = (int *)ft_calloc(sizeof(int), 2);
		if (!(*cmd_tokens)->file_type)
			ft_error("Malloc failed", MALLOC, 0);
		(*cmd_tokens)->file_type[1] = 0;
	}
	else
	{
		(*cmd_tokens)->file_redir = (char **)ft_realloc((*cmd_tokens)->file_redir, sizeof(char *) * (i + 1), sizeof(char *) * (i + 2));
		(*cmd_tokens)->file_redir[i + 1] = NULL;
		(*cmd_tokens)->file_type = (int *)ft_realloc((*cmd_tokens)->file_type, sizeof(int) * (i + 1), sizeof(int) * (i + 2));
		(*cmd_tokens)->file_type[i + 1] = 0;
	}
}

// function: store the heredoc into a tem_heredoc_file(1st argument) line by line followed a newline
// return: -1 means error and handle this, no more free in this function
// after call: 	delete the tmp_heredoc_file after this cmd_node, and strongly recommend to use different file_name for 1st argument
// 				<< heredoc 需要将每行都要执行参数扩展、命令替换以及算术扩展

static int store_heredoc(char *line, t_input *input, t_list *env_lst, int fd)
{
	char	*heredoc;

	if (!line && !errno) // 相当于SIGTERM
	{
		g_exitcode = 256; // 在输出的时候强制转换为unsigned int
		printf("\033[1A"); // 光标向上移动一行
		rl_redisplay(); // 重新显示"heredoc >>"
		return (1);
	}
	if (!ft_strncmp(line, input->temp_line, ft_strlen(input->temp_line))
		&& ft_strlen(input->temp_line) == ft_strlen(line) && free_str(line))
		return (1);
	else
	{ // expand the $(...)
		if (ft_strchr(line, '$') && !input->quote_type) // << "q" cat不扩展
			line = replace_env_expand(line, env_lst);
		heredoc = ft_strjoin(line, "\n");
		if (!heredoc)
			ft_error("Malloc failed", MALLOC, 0);
		free_str(line);
		if (write(fd, heredoc, ft_strlen(heredoc)) == -1)
			ft_error("Open tmp_file failed", FILE_OP, 0);
		free_str(heredoc);
	}
	return (0);
}

static void handle_heredoc(t_list *env_lst, t_input *input, char *num_heredoc)
{
	int		fd; // for tmp_file, store the heredoc
	char	*line;
	char	*file_name;

	file_name = ft_strjoin("heredoc_name", num_heredoc);
	fd = open(file_name, O_WRONLY|O_CREAT|O_TRUNC, 0644);// 读写/读/读
	if (fd < 0)
		ft_error("Open tmp_file failed", FILE_OP, 0);
	free_str(file_name);
	while(g_exitcode != -2)
	{
		signal(SIGINT, handle_signal_heredoc);
		line = readline("heredoc >> ");
		if (store_heredoc(line, input, env_lst, fd) == 1)
			break;
	}
	close(fd);
	if (g_exitcode == -2)
		g_exitcode = 1;
	return ;
}

void redir_heredoc(t_token *cmd_tokens, t_list *line_lst, t_list *env_lst, int i)
{
	char	*num_heredoc;

	num_heredoc = ft_itoa(cmd_tokens->cmd_id);
	handle_heredoc(env_lst, ((t_input *)line_lst->next->content), num_heredoc);
	cmd_tokens->file_redir[i] = ft_strjoin("heredoc_name", num_heredoc); // tmp_file_name same with in handle_heredoc
	if (!cmd_tokens->file_redir[i])
		ft_error("Malloc failed", MALLOC, 0);
	free_str(num_heredoc);
	cmd_tokens->file_type[i] = 3; // 3 for infile <
	cmd_tokens->num_infile += 1;
}

void create_lst(t_list **lst, void *content)
{
	t_list	*node;

	node = ft_lstnew(content);
	if (!node)
		ft_error("Malloc failed", MALLOC, 0);
	ft_lstadd_back(lst, node);
}
