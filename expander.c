#include "minishell.h"

// call this function between lexer and parser
// 把带有$标识的环境变量替换成相应的变量值；
// 1. char **tmp_exp = ft_split (temp_line, $)
// 2. 除了第一项，全部进行替换；
// 3. 查找ft_strnstr(tmp_exp[i], env_name[j], ft_strlen(env_name[j]))，只检测开头与env_name一致的值
// 4. 找到之后，tmp_substr = ft_substr(tmp_exp[i], ft_strlen(env_name[j]), ft_strlen(tmp_exp[i]))
// 5. exp_line = ft_strjoin(env_value[j], tmp_substr);
// 6. free(temp_line); temp_line = NULL; temp_line = exp_line;

// handle $?, use the waitpid() status of process, tips: WEXITSTATUS(), WIFEXITED(), WIFSIGNALED()
char *handle_exitcode(int status, char *str) // test$?-test => test0-test
{
	char *str_status = NULL; // itoa(status)
	char *res = NULL;

	str_status = ft_itoa(status);
	res = ft_strjoin(str_status, str + 1); // 去掉'?'
	free(str_status);
	str_status = NULL;
	free(str);
	str = NULL;
	return (res);
}

// replace the env_name with env_value, expand the args
void handle_expand(t_list *line_lst, t_list *env_lst, int status) // status is the exitcode of the previous process
{
	int i;
	int j;
	int isExpand = 0;
	int len_envp = 0;
	char **tmp_exp = NULL; // $ split每个temp_line
	char *tmp_substr = NULL; // 找到环境变量之后，去除env_name的子串
	char *exp_line = NULL; // 组合成一个扩展之后的字符串
	char *tmp_join = NULL; // for free， strjoin的第一个参数

	while (line_lst)
	{
		if (((t_input *)line_lst->content)->quote_type != 1 && ft_strchr(((t_input *)line_lst->content)->temp_line, '$'))
		{
			tmp_exp = ft_split(((t_input *)line_lst->content)->temp_line, '$');
			if (!tmp_exp)
				ft_error("Malloc failed", MALLOC);
			if (((t_input *)line_lst->content)->temp_line[0] == '$')
				i = 0; // the first arg need to handle $
			else
			 	i = 1; // the first arg no need to handle

			while (tmp_exp[i])
			{
				if (tmp_exp[i][0] != '?')
				{
					while (((char **)env_lst->content)[0]) // iterate the all the env names
					{
						len_envp = ft_strlen(((char **)env_lst->content)[0]);
						if (ft_strnstr(tmp_exp[i], ((char **)env_lst->content)[0], len_envp) && !ft_isalnum(tmp_exp[i][len_envp])) // 判断下一个是否是特殊字符（！数字！字母）
						{
							tmp_substr = ft_substr(tmp_exp[i], len_envp, ft_strlen(tmp_exp[i])); // 内部已经free了tmp_exp
							if (!tmp_substr)
								ft_error("Syntax error", SYNTAX);
							free(tmp_exp[i]);
							tmp_exp[i] = NULL;

							exp_line = ft_strjoin(((char **)env_lst->content)[1], tmp_substr);
							if (!exp_line)
								ft_error("Syntax error", SYNTAX);
							free(tmp_substr);
							tmp_substr = NULL;
							tmp_exp[i] = ft_strdup(exp_line);
							free(exp_line);
							exp_line = NULL;
							isExpand = 1;
							break;
						}
						env_lst = env_lst->next;
					}
					// replace the invalid envp to null
					if (!isExpand)
					{
						free(tmp_exp[i]);
						tmp_exp[i] = NULL;
						tmp_exp[i] = ft_strdup("");
					}
				}
				else
					tmp_exp[i] = handle_exitcode(status, tmp_exp[i]);
				i++;
			}
			j = i; // 复用一下
			i = 0;
			// 展开后的tmp_exp，又重新连接起来，形成新的temp_line后续parser使用，并且free原来的temp_line
			free(((t_input *)line_lst->content)->temp_line);
			((t_input *)line_lst->content)->temp_line = NULL;
			((t_input *)line_lst->content)->temp_line = ft_strdup("");
			if (!(((t_input *)line_lst->content)->temp_line))
				ft_error("Malloc failed", MALLOC);
			while (i < j)
			{
				tmp_join = ((t_input *)line_lst->content)->temp_line;
				((t_input *)line_lst->content)->temp_line = ft_strjoin(tmp_join, tmp_exp[i]);
				if (!(((t_input *)line_lst->content)->temp_line))
					ft_error("Malloc failed", MALLOC);
				free(tmp_join);
				tmp_join = NULL;
				i++;
			}
			free_char(tmp_exp);
		}
		line_lst = line_lst->next;
	}
	return ;
}
/*
int	env_init(t_mini *mini, char **env)
{
	int		i;
	char	**env_content;
	t_list	*node;

	i = 0;
	mini->env = NULL;
	while (env[i])
	{
		env_content = ft_split(env[i], '=');
		if (!env_content)
			ft_error("malloc fail or null input?\n", 1);
		node = ft_lstnew((char **)env_content);
		if (!node)
			ft_error("fail to init a node\n", 1);
		ft_lstadd_back(&mini->env, node);
		i++;
	}
	//test_env_functions(mini);
	return (1);
}

int main(int argc, char **argv, char **env)
{
	t_list *line_lst = NULL;
	t_input *input;
	char *line;
	t_list *cmd_lst = NULL;
	t_mini *mini;
	int exitcode = 0; // parent process get the child process exitcode
	int i = -1;

	mini = malloc(sizeof(t_mini) * 1);
	if (!mini)
		ft_error("Malloc fail.\n", 1);
	if (env_init(mini, env) != 1)
		ft_error("fail to init env variables.", 3);
	while (1)
	{
		line = readline("\033[32m\U0001F40C Minishell \033[31m$\033[0;39m ");
		if (!line)
			ft_error("Readline failed.\n", 4);
		if (ft_strncmp(line, "q", 2) == 0)
		{
			free(line);
			break ;
		}
		add_history(line);

		line_lst = get_linelst(line);
		handle_expand(line_lst, mini->env, exitcode);
		cmd_lst = parse_cmds(line_lst);
		ft_lstfree(line_lst);
		while (cmd_lst)
		{
			printf("cmd: %s\n", ((t_token *)cmd_lst->content)->cmd);
			i = 0;
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
		free(line);
		line = NULL;
	}
	clear_history();
	return (0);
} */

// <<"EOF" <infile 'ls' "-l" | grep "test" >outfile >>'out2' test$?test 42$PWD-hive
// < infile 'ls' "-l" |wc -l > outfile
