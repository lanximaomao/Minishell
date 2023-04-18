#include "minishell.h"

// call this function between lexer and parser
// 把带有$标识的环境变量替换成相应的变量值；
// 1. char **tmp_exp = ft_split (temp_line, $)
// 2. 除了第一项，全部进行替换；
// 3. 查找ft_strnstr(tmp_exp[i], env_name[j], ft_strlen(env_name[j]))，只检测开头与env_name一致的值
// 4. 找到之后，tmp_substr = ft_substr(tmp_exp[i], ft_strlen(env_name[j]), ft_strlen(tmp_exp[i]))
// 5. exp_line = ft_strjoin(env_value[j], tmp_substr);
// 6. free(temp_line); temp_line = NULL; temp_line = exp_line;



// handle the $?, use the waitpid() status of process, tips: WEXITSTATUS(), WIFEXITED(), WIFSIGNALED()
char *handle_expand(t_list *line_lst, t_env *env)
{
	int i;
	int j;
	int len_envp = 0;
	char **tmp_exp = NULL;
	char *tmp_substr = NULL;
	char *exp_line = NULL;

	while (line_lst)
	{
		if (((t_input *)line_lst->content)->quote_type != 1 && ft_strchr(((t_input *)line_lst->content)->temp_line, '$'))
		{
			tmp_exp = ft_split(((t_input *)line_lst->content)->temp_line, '$');
			if (!tmp_exp)
				ft_error("Malloc failed", MALLOC);
			free(((t_input *)line_lst->content)->temp_line); // 为后面strjoin使用，从null开始连接
			((t_input *)line_lst->content)->temp_line = NULL;
			i = 1;
			while (tmp_exp[i])
			{
				j = 0;
				while (env->env_name[j]) // getenv("PATH")
				{
					len_envp = ft_strlen(env_name[j]);
					if (ft_strnstr(tmp_exp[i], env_name[j], len_envp) && !ft_isalnum(tmp_exp[i][len])) // 判断下一个是否是特殊字符（！数字！字母）
					{
						tmp_substr = ft_substr(tmp_exp[i], len_envp, ft_strlen(tmp_exp[i])); // 内部已经free了tmp_exp
						if (!tmp_substr)
						{
							perror("Malloc error.\n");
							free_char(tmp_exp);
							return (NULL);
						}
						exp_line = ft_strjoin(env->env_value[j], tmp_substr);
						if (!exp_line)
						{
							perror("Malloc error.\n");
							free_char(tmp_exp);
							return (NULL);
						}
						free(tmp_substr);
						tmp_substr = NULL;
						free(tmp_exp[i]);
						tmp_exp[i] = NULL;
						tmp_exp[i] = exp_line;
						free(exp_line);
						exp_line = NULL;
						break;
					}
					j++;
				}
				if (tmp_exp[i])
					tmp_exp[i] = NULL;
				i++;
			}
			j = i; // 复用一下
			i = 0;
			// 展开后的tmp_exp，又重新连接起来，形成新的temp_line后续parser使用，并且free原来的temp_line
			while (i < j)
			{
				char *tmp = NULL; // free strjoin的第一个参数
				tmp = ((t_input *)line_lst->content)->temp_line;
				((t_input *)line_lst->content)->temp_line = ft_strjoin(((t_input *)line_lst->content)->temp_line, tmp_exp[i]);
				if (!((t_input *)line_lst->content)->temp_line)
				{
					perror("Malloc error.\n");
					free_char(tmp_exp);
					return (NULL);
				}
				free(tmp);
				tmp = NULL;
				i++;
			}
			free_char(tmp_exp);
		}
		line_lst = line_lst->next;
	}
	return ;
}


// ***********************handle $?
void handle_exitcode()
{

}

int main(int argc, char **argv)
{
	t_list *line_lst = NULL;
	t_input *input;
	char *line;
	t_list *cmd_lst = NULL;

	while (1)
	{
		line = readline("minishell\033[31m$\033[0;39m ");
		add_history(line);

		line_lst = get_linelst(line);
		if (!line_lst)
			printf("test1\n");
		cmd_lst = parse_cmds(line_lst);
		if (!cmd_lst)
			printf("test2\n");
		ft_lstfree(line_lst);
		while (cmd_lst)
		{
			printf("cmd: %s\n", ((t_token *)cmd_lst->content)->cmd);
			// printf("%s\n", ((t_token *)cmd_lst->content)->args[0]);
			// printf("%s\n", ((t_token *)cmd_lst->content)->infile[0]);
			// printf("%s\n", ((t_token *)cmd_lst->content)->outfile[0]);
			// printf("%d\n", ((t_token *)cmd_lst->content)->output_type[0]);
			printf("num_args: %d\n", ((t_token *)cmd_lst->content)->num_args);
			printf("num_infile: %d\n", ((t_token *)cmd_lst->content)->num_infile);
			printf("num_outfile_type: %d\n", ((t_token *)cmd_lst->content)->num_outfile_type);
			printf("expand_sign: %d\n", ((t_token *)cmd_lst->content)->expander_sign);
			cmd_lst = cmd_lst->next;
		}
		if (ft_strncmp(line, "exit", 4) == 0)
		{
			free(line);
			break ;
		}
	}
	return (0);
}

