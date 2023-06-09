#include "minishell.h"

int	free_str(char *str)
{
	free(str);
	str = NULL;
	return (1);
}

void	free_char(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i] != NULL)
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

void	free_input(t_input *input)
{
	if (input != NULL)
	{
		if (input->tmp_line != NULL)
		{
			free(input->tmp_line);
			input->tmp_line = NULL;
		}
		input->quote_type = 0;
		input->pipe_sign = 0;
		input->redir_sign = 0;
		free(input);
		input = NULL;
	}
}

void	free_tokens(t_token *tokens)
{
	if (tokens != NULL)
	{
		if (tokens->cmd != NULL)
			free_str(tokens->cmd);
		if (tokens->args != NULL)
			free_char(tokens->args);
		if (tokens->file_redir != NULL)
			free_char(tokens->file_redir);
		if (tokens->file_type != NULL)
		{
			free(tokens->file_type);
			tokens->file_type = NULL;
		}
		free(tokens);
		tokens = NULL;
	}
}

/*
** sign = 0 for line_list, 1 for cmd_lst, 2 for env_lst
*/
void	free_lst_content(t_list *lst, int sign)
{
	t_list	*tmp;

	tmp = lst;
	while (lst)
	{
		if (sign == 0)
			free_input((t_input *)lst->content);
		else if (sign == 1)
			free_tokens((t_token *)lst->content);
		else if (sign == 2)
			free_char((char **)lst->content);
		lst = lst->next;
	}
	ft_lstfree(tmp);
	return ;
}
