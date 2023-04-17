#include "minishell.h"


// input line_lst return tokens, in here, one token is one complete cmd
t_list *parse_tokens(t_list *line_lst)
{
	int i = 0;
	int fd = 0;
	t_list *tokens_lst = NULL;
	t_list *node = NULL;
	t_token *token;

	node = ft_lstnew((t_token *)line_lst->content);
	if (!node)
	{
		ft_printf("malloc Failed.");
		return (NULL);
	}

	while (line_lst)
	{

		if (((t_input *)line_lst->content)->redir_sign = 1)
			node->infile = ((t_input *)line_lst->content)->next->temp_line;




		if (((t_input *)line_lst->content)->pipe_sign = 1)
		{
			ft_lstadd_back(&tokens_lst, node);
		}

		line_lst = line_lst->next;
	}
	return (token);
}


// < infile 'ls' "-l" | wc -l > outfile

