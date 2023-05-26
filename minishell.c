#include "minishell.h"
#include "builtin.h"
#include "executor.h"
#include "signal.h"

void minishell(t_mini *mini, char *line, int exitcode)
{
	int i;
	t_list *line_lst;
	line_lst = NULL;
	int size;

	//lexer parser and expander, and heredoc is also handled here
	//check for parsing error
	line_lst = get_linelst(line, line_lst, -1);
	free(line);
	line = NULL;
	if (handle_args_expand(line_lst, mini->env) == -1)
		return ;
	mini->cmd_lst = parse_cmds(line_lst, mini->env, 0);
	// print the line_lst
	// t_list *tmp_tmp = line_lst;
	// while (tmp_tmp)
	// {
	// 	printf("temp_line: %s\n", ((t_input *)tmp_tmp->content)->temp_line);
	// 	printf("pipe_sign: %d\n", ((t_input *)tmp_tmp->content)->pipe_sign);
	// 	printf("redir_sign: %d\n", ((t_input *)tmp_tmp->content)->redir_sign);
	// 	tmp_tmp = tmp_tmp->next;
	// }

	ft_lstfree(line_lst);

	// test the result of cmd_lst without executor
	// t_list *tmp = mini->cmd_lst; // add by Lin

	// while (tmp)
	// {
	// 	printf("cmd: %s\n", ((t_token *)tmp->content)->cmd);
	// 	printf("num_args=%d\n", ((t_token *)tmp->content)->num_args);
	//	printf("num_infile=%d\n", ((t_token *)tmp->content)->num_infile);
	//	printf("num_outfile=%d\n", ((t_token *)tmp->content)->num_outfile_type);
	//	i = 0; // ignore the first arg which is cmd
	//	while (i < ((t_token *)tmp->content)->num_args)
	//		printf("args: %s\n", ((t_token *)tmp->content)->args[i++]);
	//	printf("\n******************************************************\n\n");
		//i = 0;
		//while (i < ((t_token *)tmp->content)->num_infile)
		//	printf("infile: %s\n", ((t_token *)tmp->content)->infile[i++]);
		//i = 0;
		//while (i < ((t_token *)tmp->content)->num_outfile_type)
		//{
		//	printf("outfile: %s\n", ((t_token *)tmp->content)->outfile[i]);
		//	printf("output_type: %d\n", ((t_token *)tmp->content)->output_type[i++]);
		//}
	// 	tmp = tmp->next;
	// 	if (tmp)
	// 		printf("\n****************the next cmd*****************\n");
	// }
	// check for single builtin, if yes, just function call and return
	signal(SIGQUIT, handle_cmd);
	signal(SIGINT, handle_cmd);
	size = ft_lstsize(mini->cmd_lst);
	if (size == 0)
		return;
	//signal_cat();//
	//if (size == 1)
	//{
	//	printf("exitcode05=%d\n", g_exitcode);
	//	executor_single(mini);
	//	printf("exitcode06=%d\n", g_exitcode);
	//}

	//else
		executor(mini, size);
}
// <<"EOF" <infile 'ls' "-l" | grep "test" >outfile >>'out2' test$?test 42$PWD-hive
// < infile 'ls' "-l" |wc -l > outfile
