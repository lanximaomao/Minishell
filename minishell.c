#include "minishell.h"
#include "buidin.h"

void minishell(t_mini *mini, char *line, int exitcode)
{
	int i;
	t_list *line_lst;
	t_list *tmp;
	line_lst = NULL;

	//lexer parser and expander, and heredoc is also handled here
	//check for parsing error
	line_lst = get_linelst(line, line_lst, -1);
	free(line);
	line = NULL;
	// handle_error in here.
	handle_args_expand(line_lst, mini->env, exitcode);
	mini->cmd_lst = parse_cmds(line_lst, mini->env, 0);
	ft_lstfree(line_lst);
	line_lst = NULL;

	// test the result of cmd_lst without executor
	//tmp = mini->cmd_lst; // add by Lin

	//while (tmp)
	//{
		//printf("cmd: %s\n", ((t_token *)tmp->content)->cmd);
		//printf("num_infile=%d\n", ((t_token *)tmp->content)->num_infile);
		//printf("num_outfile=%d\n", ((t_token *)tmp->content)->num_outfile_type);
		//i = 0; // ignore the first arg which is cmd
		//while (i < ((t_token *)tmp->content)->num_args)
		//	printf("args: %s\n", ((t_token *)tmp->content)->args[i++]);
		//i = 0;
		//while (i < ((t_token *)tmp->content)->num_infile)
		//	printf("infile: %s\n", ((t_token *)tmp->content)->infile[i++]);
		//i = 0;
		//while (i < ((t_token *)tmp->content)->num_outfile_type)
		//{
		//	printf("outfile: %s\n", ((t_token *)tmp->content)->outfile[i]);
		//	printf("output_type: %d\n", ((t_token *)tmp->content)->output_type[i++]);
		//}
	//	tmp = tmp->next;
	//	if (tmp)
	//		printf("\n****************the next cmd*****************\n");
	//}
	// check for single buildin, if yes, just function call and return


	if (ft_lstsize(mini->cmd_lst) == 1 && is_buildin(mini->cmd_lst, mini->env) == 1)
	 	return;
	// if not a buildin or there is more than one buidin, start to fork....
	executor(mini); // find at executor.c
}


// <<"EOF" <infile 'ls' "-l" | grep "test" >outfile >>'out2' test$?test 42$PWD-hive
// < infile 'ls' "-l" |wc -l > outfile
