#include "minishell.h"


// input line_lst return tokens, in here, one token is one complete cmd
t_list *parse_tokens(t_list *line_lst)
{
	int i = 0;
	int fd = 0;
	t_list *tokens_lst = NULL;
	t_list *node = NULL;
	t_token *token;


	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);

	while (line_lst)
	{ // handle 2<>outfile等等，不能有两个连着的
		while (((t_input *)line_lst->content)->pipe_sign != 1)
		{

			if (((t_input *)line_lst->content)->redir_sign = 1)
			{ // each redirection file cannot be empty, parse error
				token->infile = ((t_input *)line_lst->content)->next->temp_line;
				token->infile++;
			}
			if (((t_input *)line_lst->content)->redir_sign = 3 || ((t_input *)line_lst->content)->redir_sign = 4)
			{ // each redirection file cannot be empty, parse error
				token->outfile = ((t_input *)line_lst->content)->next->temp_line;
				token->outfile++;
			}
			if (((t_input *)line_lst->content)->redir_sign = 2)
			{
				// heredoc 新建一个临时文件，存入输入到数据，并将临时文件的路径保存在token->infile中
			}
			if (((t_input *)line_lst->content)->redir_sign = 5)
			{
				// error
			}






			line_lst = line_lst->next;
		}
		node = ft_lstnew((t_token *)token);
		if (!node)
		{
			ft_printf("Malloc Failed.");
			return (NULL);
		}
		ft_lstadd_back(&tokens_lst, node);
		line_lst = line_lst->next;
	}

	return (token);
}


// < infile 'ls' "-l" | wc -l > outfile

