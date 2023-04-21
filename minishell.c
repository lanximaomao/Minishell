#include "minishell.h"
#include "buidin.h"
#include "pipe.h"

void minishell(t_mini *mini, char *line, int exitcode)
{
	int i;
	t_list *line_lst;
	t_list *cmd_lst;
	t_input *input;
	t_token* cmd_tokens;

	line_lst = NULL;
	cmd_lst = (t_list *)mini->cmd_lst;
	input = (t_input *)line_lst->content;
	cmd_tokens = (t_token *)cmd_lst->content;

	//lexer parser and expander, and heredoc is also handled here
	//check for parsing error

	line_lst = get_linelst(line, line_lst, -1);
	free(line);
	line = NULL;
	// handle_error in here.
	handle_args_expand(line_lst, mini->env, exitcode);
	cmd_lst = parse_cmds(line_lst, mini->env, 0);
	ft_lstfree(line_lst);
	line_lst = NULL;

	// check for single buildin, if yes, just function call and return
	if (ft_lstsize(cmd_lst) == 1 && is_buildin(cmd_tokens->args, mini->env) == 1)
		return;
	// if not a buildin or there is more than one buidin, start to fork....
	executor(mini); // find at executor.c
}
