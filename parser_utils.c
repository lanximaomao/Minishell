#include "minishell.h"

void	malloc_redir(t_token **cmd_tokens, int i)
{
	if (i == 0)
	{
		(*cmd_tokens)->file_redir = (char **)ft_calloc(sizeof(char *), 2);
		if (!(*cmd_tokens)->file_redir)
			ft_error(" minishell: malloc fail", MALLOC, 0);
		(*cmd_tokens)->file_redir[1] = NULL;
		(*cmd_tokens)->file_type = (int *)ft_calloc(sizeof(int), 2);
		if (!(*cmd_tokens)->file_type)
			ft_error(" minishell: malloc fail", MALLOC, 0);
		(*cmd_tokens)->file_type[1] = 0;
	}
	else
	{
		(*cmd_tokens)->file_redir = (char **)ft_realloc((*cmd_tokens)
			->file_redir, sizeof(char *) * (i + 1), sizeof(char *) * (i + 2));
		if (!(*cmd_tokens)->file_redir)
			ft_error(" minishell: malloc fail", MALLOC, 0);
		(*cmd_tokens)->file_redir[i + 1] = NULL;
		(*cmd_tokens)->file_type = (int *)ft_realloc((*cmd_tokens)->file_type,
			sizeof(int) * (i + 1), sizeof(int) * (i + 2));
		if (!(*cmd_tokens)->file_type)
			ft_error(" minishell: malloc fail", MALLOC, 0);
		(*cmd_tokens)->file_type[i + 1] = 0;
	}
}

/*
** << "q" cat不扩展
*/
static int	store_heredoc(char *line, t_input *input, t_list *env_lst, int fd)
{
	char	*heredoc;

	if (!line && !errno)
	{
		g_exitcode = 256;
		ft_printf("\033[1A");
		rl_redisplay();
		return (1);
	}
	if (!ft_strncmp(line, input->tmp_line, ft_strlen(input->tmp_line))
		&& ft_strlen(input->tmp_line) == ft_strlen(line) && free_str(line))
		return (1);
	else
	{
		if (ft_strchr(line, '$') && !input->quote_type)
			line = replace_env_expand(line, env_lst);
		heredoc = ft_strjoin(line, "\n");
		if (!heredoc)
			ft_error(" minishell: malloc fail", MALLOC, 0);
		free_str(line);
		if (write(fd, heredoc, ft_strlen(heredoc)) == -1)
			ft_error(" minishell: open tmp_file failed", FILE_OP, 0);
		free_str(heredoc);
	}
	return (0);
}

static char	*handle_heredoc(t_list *env_lst, t_input *input, char *num_heredoc)
{
	int		fd;
	char	*line;
	char	*file_name;

	file_name = ft_strjoin("tmp_file", num_heredoc);
	if (!file_name)
		ft_error(" minishell: malloc fail", MALLOC, 0);
	free_str(num_heredoc);
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		ft_error(" minishell: open tmp_file failed", FILE_OP, 0);
	while (g_exitcode != -2)
	{
		signal(SIGINT, handle_signal_heredoc);
		line = readline("heredoc >> ");
		if (store_heredoc(line, input, env_lst, fd) == 1)
			break ;
	}
	close(fd);
	if (g_exitcode == -2)
		g_exitcode = 513;
	return (file_name);
}

void	redir_heredoc(t_token *cmd_tokens, t_list *line_lst, t_list *env_lst,
		int i)
{
	char	*num_heredoc;
	char	*file_name;

	num_heredoc = ft_itoa(cmd_tokens->cmd_id);
	if (!num_heredoc)
		ft_error(" minishell: malloc fail", MALLOC, 0);
	file_name = handle_heredoc(env_lst, ((t_input *)line_lst->next->content),
			num_heredoc);
	if (g_exitcode == 513)
	{
		free_str(file_name);
		return ;
	}
	cmd_tokens->file_redir[i] = ft_strdup(file_name);
	if (!cmd_tokens->file_redir[i])
		ft_error(" minishell: malloc fail", MALLOC, 0);
	free_str(file_name);
	cmd_tokens->file_type[i] = 3;
	cmd_tokens->num_infile += 1;
}

void	create_lst(t_list **lst, void *content)
{
	t_list	*node;

	node = ft_lstnew(content);
	if (!node)
		ft_error(" minishell: malloc fail", MALLOC, 0);
	ft_lstadd_back(lst, node);
}
