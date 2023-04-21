#include "minishell.h"
#include "buidin.h"

void minishell(t_mini *mini, char *line, int exitcode)
{
	int i;
	t_list *line_lst;
	t_list *cmd_lst;
	line_lst = NULL;
	cmd_lst = (t_list *)mini->cmd_lst;
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

	// test the result of cmd_lst without executor
	while (cmd_lst)
	{
		printf("cmd: %s\n", ((t_token *)cmd_lst->content)->cmd);
		i = 1; // ignore the first arg which is cmd
		while (i < ((t_token *)cmd_lst->content)->num_args)
			printf("args: %s\n", ((t_token *)cmd_lst->content)->args[i++]);
		i = 0;
		while (i < ((t_token *)cmd_lst->content)->num_infile)
			printf("infile: %s\n", ((t_token *)cmd_lst->content)->infile[i++]);
		i = 0;
		while (i < ((t_token *)cmd_lst->content)->num_outfile_type)
		{
			printf("outfile: %s\n", ((t_token *)cmd_lst->content)->outfile[i]);
			printf("output_type: %d\n", ((t_token *)cmd_lst->content)->output_type[i++]);
		}
		cmd_lst = cmd_lst->next;
		if (cmd_lst)
			printf("\n****************the next cmd*****************\n");
	}

	// check for single buildin, if yes, just function call and return
	// if (ft_lstsize(cmd_lst) == 1 && is_buildin(cmd_tokens->args, mini->env) == 1)
	// 	return;
	// if not a buildin or there is more than one buidin, start to fork....
	executor(mini); // find at executor.c
}


// <<"EOF" <infile 'ls' "-l" | grep "test" >outfile >>'out2' test$?test 42$PWD-hive
// < infile 'ls' "-l" |wc -l > outfile
