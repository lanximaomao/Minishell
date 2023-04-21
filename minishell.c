#include "minishell.h"
#include "buidin.h"
#include "pipe.h"

void minishell(t_mini *mini, char *line)
{
	int i;
	t_list *line_lst;
	t_list *cmd_lst;
	t_input *input;
	t_token* token;

	line_lst = NULL;
	cmd_lst = NULL;

	if (*line == '\0')
		return;

	//lexer parser and expander, and heredoc is also handelled here
	//check for parsing error

	while (1)
	{
		line_lst = get_linelst(line, line_lst, -1);
		free(line);
		line = NULL;
		handel_args_expamd(line_lst, mini->env, exitcode);
		cmd_lst = parse_cmds(line_lst, mini->env, 0);
		ft_lstfree(line_lst);
		line_lst = NULL;
	}

	//printing out the result from lexer, parser and expander
	token = (t_token*)cmd_lst->content;
	while (cmd_lst)
	{
		printf("cmd:%s\n", token->cmd);
		i = -1;
		while (++i < token->num_args)
			printf("args:%s\n", token->args[i]);
		i = -1;
		while (++i < token->num_infile)
			printf("infile:%s\n", token->infile[i]);
		i = -1;
		while (++i < token->num_outfile_type )
		{
			printf("outfille:%s\n", token->outfile[i]);
			printf("output_type:%d\n", token->output_type[i]);
		}
		cmd_lst = cmd_lst->next;
		if (cmd_lst)
			printf("\n*****************the next cmd*****************\n");
	}
	// check for single buildin, if yes, just function call and return
	if (ft_lstsize(mini->cmd_lst) == 1 && is_buildin(token->args, mini->env) == 1)
		return;

	// if not a buildin or there is more than one buidin, start to fork....
	executor(mini); // find at executor.c
}
