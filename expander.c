
#include "minishell.h"

// handle $?, use the waitpid() status of process, tips: WEXITSTATUS(), WIFEXITED(), WIFSIGNALED()
char *handle_exitcode(int exitcode, char *str) // test$?-test => test0-test
{
	char *str_status = NULL; // itoa(status)
	char *res = NULL;

	str_status = ft_itoa(exitcode);
	res = ft_strjoin(str_status, str + 1); // 去掉'?'
	free(str_status);
	str_status = NULL;
	free(str);
	str = NULL;
	return (res);
}

// find the env_name and replace it with env_value
char *replace_env(char *tmp_exp, t_list *env_lst, char *tmp_substr, int len_envp) // tmp_substr, 找到环境变量之后，去除env_name的子串
{
	while (env_lst) // iterate the all the env names
	{
		len_envp = ft_strlen(((char **)env_lst->content)[0]);
		if (ft_strnstr(tmp_exp, ((char **)env_lst->content)[0], len_envp)
			 && !ft_isalnum(tmp_exp[len_envp])) // 判断下一个是否是特殊字符（！数字！字母）
		{
			if (!(tmp_substr = ft_substr(tmp_exp, len_envp, ft_strlen(tmp_exp))))
				ft_error("Malloc failed", MALLOC);
			free_str(tmp_exp);
			if (!(tmp_exp = ft_strdup(ft_strjoin(((char **)env_lst->content)[1], tmp_substr))))
				ft_error("Malloc failed", MALLOC);
			free_str(tmp_substr);
			len_envp = -1; // 复用， for norm
			break;
		}
		env_lst = env_lst->next;
	}
	if (len_envp != -1)
	{
		free_str(tmp_exp);
		tmp_exp = ft_strdup("");
	}
	return (tmp_exp);
}

// 展开后的tmp_exp，又重新连接起来，形成新的temp_line后续parser使用，并且free原来的temp_line
char *ft_mulstrjoin(char **tmp_exp, int len) // len is the length of tmp_exp
{
	int i;
	char *tmp_join;
	char *res;

	i = 0;
	tmp_join = NULL; // for free， strjoin的第一个参数
	res = NULL;
	if (!(res = ft_strdup("")))
		ft_error("Malloc failed", MALLOC);
	while (i < len)
	{
		tmp_join = res;
		res = ft_strjoin(tmp_join, tmp_exp[i]);
		if (!res)
			ft_error("Malloc failed", MALLOC);
		free_str(tmp_join);
		i++;
	}
	return res;
}

// split, replace, joint, return
// for reuse this function in heredoc
char *replace_env_expand(char *temp_line, t_list *env_lst, int exitcode)
{
	int i;
	char **tmp_exp; // $ split每个temp_line

	i = -1;
	tmp_exp = NULL;
	tmp_exp = ft_split(temp_line, '$');
	if (!tmp_exp)
		ft_error("Malloc failed", MALLOC);
	if (temp_line[0] != '$')
		i = 0; // the first arg no need to handle
	free(temp_line);
	temp_line = NULL;
	while (tmp_exp[++i])
	{
		if (tmp_exp[i][0] == '?')
			tmp_exp[i] = handle_exitcode(exitcode, tmp_exp[i]);
		else
			tmp_exp[i] = replace_env(tmp_exp[i], env_lst, NULL, -1);
	}
	temp_line = ft_mulstrjoin(tmp_exp, i);
	free_char(tmp_exp);
	return temp_line;
}

void handle_args_expand(t_list *line_lst, t_list *env_lst, int exitcode) // status is the exitcode of the previous process
{
	while (line_lst)
	{
		//if (!ft_strncmp(((t_input *)line_lst->content)->temp_line, "", 1)) // handle error: parse error, '| |', '< >', '> <<'
		//{
		//	if (line_lst->next && !ft_strncmp(((t_input *)line_lst->next->content)->temp_line, "", 1))
		//		ft_error("Syntax error: parse error.", SYNTAX);
		//}
		if (((t_input *)line_lst->content)->quote_type != 1
			 && ft_strchr(((t_input *)line_lst->content)->temp_line, '$'))
			((t_input *)line_lst->content)->temp_line = replace_env_expand(((t_input *)line_lst->content)->temp_line, env_lst, exitcode);

		line_lst = line_lst->next;
	}
}
