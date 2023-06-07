#include "minishell.h"

static void	init_tokens(t_token *tokens, int num_cmd)
{
	tokens->cmd = NULL;
	tokens->args = NULL;
	tokens->file_redir = NULL;
	tokens->file_type = NULL;
	tokens->cmd_id = num_cmd;
	tokens->num_infile = 0;
	tokens->num_outfile = 0;
	tokens->num_args = 0;
	tokens->fd_in = 0;
	tokens->fd_out = 1;
}

/*
** redir_sign 1 for <, 2 for <<, 3 for >, 4 for >>
*/
static void	parse_redir(t_token *cmd_tokens, t_list *line_lst, t_list *env_lst,
		int i)
{
	malloc_redir(&cmd_tokens, i);
	if (((t_input *)line_lst->content)->redir_sign == 2)
		redir_heredoc(cmd_tokens, line_lst, env_lst, i);
	else
	{
		if (line_lst->next)
			cmd_tokens->file_redir[i] = ft_strdup(((t_input *)
						line_lst->next->content)->tmp_line);
		if (!cmd_tokens->file_redir[i])
			ft_error(" minishell: malloc fail", MALLOC, 0);
		if (((t_input *)line_lst->content)->redir_sign == 1)
		{
			cmd_tokens->file_type[i] = 3;
			cmd_tokens->num_infile += 1;
		}
		else
		{
			if (((t_input *)line_lst->content)->redir_sign == 3)
				cmd_tokens->file_type[i] = 1;
			else if (((t_input *)line_lst->content)->redir_sign == 4)
				cmd_tokens->file_type[i] = 2;
			cmd_tokens->num_outfile += 1;
		}
	}
	return ;
}

static void	parse_cmd_args(t_token *cmd_tokens, t_input *input, int j)
{
	if (j == 0)
	{
		cmd_tokens->cmd = ft_strdup(input->tmp_line);
		if (!(cmd_tokens->cmd))
			ft_error(" minishell: malloc fail", MALLOC, 0);
	}
	if (j == 0)
	{
		cmd_tokens->args = (char **)ft_calloc(sizeof(char *), 2);
		if (!(cmd_tokens->args))
			ft_error(" minishell: malloc fail", MALLOC, 0);
		cmd_tokens->args[1] = NULL;
	}
	else
		cmd_tokens->args = (char **)ft_realloc(cmd_tokens->args, sizeof(char *)
				* (j + 1), sizeof(char *) * (j + 2));
	cmd_tokens->args[j] = ft_strdup(input->tmp_line);
	if (!cmd_tokens->args[j])
		ft_error(" minishell: malloc fail", MALLOC, 0);
	cmd_tokens->args[j + 1] = NULL;
	cmd_tokens->num_args += 1;
}

/*
** iterate the line_lst until | as one cmd and save it to cmd_lst
** i for num_files, j for num_cmds
*/
static t_list	*iterate_cmds(t_token *cmd_tokens, t_list *line_lst,
		t_list *env_lst)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line_lst && g_exitcode != 513)
	{
		if (((t_input *)line_lst->content)->redir_sign != 0)
		{
			parse_redir(cmd_tokens, line_lst, env_lst, i++);
			if (ft_strncmp(((t_input *)line_lst->content)->tmp_line, "", 1))
				parse_cmd_args(cmd_tokens, ((t_input *)line_lst->content), j++);
			line_lst = line_lst->next;
		}
		else if (((t_input *)line_lst->content)->pipe_sign == 0)
			parse_cmd_args(cmd_tokens, ((t_input *)line_lst->content), j++);
		if (((t_input *)line_lst->content)->pipe_sign == 1 )
			break ;
		line_lst = line_lst->next;
	}
	return (line_lst);
}

/*
** this function transforms line_lst to a command lst
** return: null means error and handle this;
** leaks: handled the error free
** after call: free the cmd_lst,
** free the line_lst from the get_linelst() in lexer.c
** if (!line_lst): 上面的redir会向下遍历一位，所以在这里判断一下是否最后，以防止segfault
*/

t_list	*parser_cmds(t_list *line_lst, t_list *env_lst)
{
	int		num_cmd;
	t_list	*cmd_lst;
	t_token	*cmd_tokens;

	num_cmd = 0;
	cmd_lst = NULL;
	cmd_tokens = NULL;
	while (line_lst)
	{
		cmd_tokens = (t_token *)ft_calloc(sizeof(t_token), 1);
		if (!cmd_tokens)
			ft_error(" minishell: malloc fail", MALLOC, 0);
		init_tokens(cmd_tokens, num_cmd);
		line_lst = iterate_cmds(cmd_tokens, line_lst, env_lst);
		create_lst(&cmd_lst, (t_token *)cmd_tokens);
		if (!line_lst)
			break ;
		num_cmd++;
		line_lst = line_lst->next;
	}
	return (cmd_lst);
}
