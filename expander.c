
#include "minishell.h"

// handle $?, use the waitpid() status of process, tips: WEXITSTATUS(), WIFEXITED(), WIFSIGNALED()
static char *handle_exitcode(char *str) // test$?-test => test0-test
{
	char *str_status = NULL; // itoa(status)
	char *res = NULL;

	str_status = ft_itoa(g_exitcode); //unsigned char
	res = ft_strjoin(str_status, str + 1); // 去掉'?'
	free(str_status);
	str_status = NULL;
	free(str);
	str = NULL;
	return (res);
}

// find the env_name and replace it with env_value
static char *replace_env(char *tmp_exp, t_list *env_lst, char *tmp_substr, int len_envp) // tmp_substr, 找到环境变量之后，去除env_name的子串
{
	while (env_lst) // iterate the all the env names
	{
		len_envp = ft_strlen(((char **)env_lst->content)[0]);
		if (ft_strnstr(tmp_exp, ((char **)env_lst->content)[0], len_envp)
			 && !ft_isalnum(tmp_exp[len_envp])) // 判断下一个是否是特殊字符（！数字！字母）
		{
			if (!(tmp_substr = ft_substr(tmp_exp, len_envp, ft_strlen(tmp_exp))))
				ft_error_minishell("Malloc failed", MALLOC, 2);
			free_str(tmp_exp);
			if (!(tmp_exp = ft_strdup(ft_strjoin(((char **)env_lst->content)[1], tmp_substr))))
				ft_error_minishell("Malloc failed", MALLOC, 2);
			free_str(tmp_substr);
			len_envp = -1; // 复用， for norm
			break;
		}
		env_lst = env_lst->next;
	}
	char *trim_str = NULL; // trim_str for "$ABS=dss", output: "=dss"
	trim_str = tmp_exp;
	if (len_envp != -1)
	{
		len_envp = 0; // reuse, as index
		while (tmp_exp)
		{
			if (!ft_isalnum(*tmp_exp))
			{
				tmp_exp = ft_strdup(tmp_exp);
				free_str(trim_str);
				break;
			}
			tmp_exp++;
		}
	}
	return (tmp_exp);
}

// 展开后的tmp_exp，又重新连接起来，形成新的temp_line后续parser使用，并且free原来的temp_line
static char *ft_mulstrjoin(char **tmp_exp, int len) // len is the length of tmp_exp
{
	int i;
	char *tmp_join;
	char *res;

	i = 0;
	tmp_join = NULL; // for free， strjoin的第一个参数
	res = NULL;
	if (!(res = ft_strdup("")))
		ft_error_minishell("Malloc failed", MALLOC, 2);
	while (i < len)
	{
		tmp_join = res;
		if (!(res = ft_strjoin(tmp_join, tmp_exp[i])))
			ft_error_minishell("Malloc failed", MALLOC, 2);
		free_str(tmp_join);
		i++;
	}
	return res;
}

// split, replace, joint, return
// for reuse this function in heredoc
char *replace_env_expand(char *temp_line, t_list *env_lst)
{
	int i;
	char **tmp_exp; // $ split每个temp_line
	char *tmp_str; // split出来的最后一个字符串，用于连接$

	i = -1;
	if (!(tmp_exp = ft_split(temp_line, '$')))
		ft_error_minishell("Malloc failed", MALLOC, 2);
	if (temp_line[0] != '$')
		i = 0; // the first arg no need to handle
	while (tmp_exp[++i])
	{
		if (tmp_exp[i][0] == '?')
			tmp_exp[i] = handle_exitcode(tmp_exp[i]);
		else if (tmp_exp[i][0] == ' ')
		{
			tmp_str = tmp_exp[i]; // 复用
			tmp_exp[i] = ft_strjoin("$", tmp_str);
			free_str(tmp_str);
		}
		else
			tmp_exp[i] = replace_env(tmp_exp[i], env_lst, NULL, -1);
	}
	// the last char is $
	if (i && temp_line[ft_strlen(temp_line) - 1] == '$')
	{
		tmp_str = tmp_exp[i - 1];
		tmp_exp[i - 1] = ft_strjoin(tmp_str, "$");
		free_str(tmp_str);
	}
	free_str(temp_line);
	if (i == 0) // echo $
		temp_line = ft_strdup("$");
	else
		temp_line = ft_mulstrjoin(tmp_exp, i);
	free_char(tmp_exp);
	return temp_line;
}

/* by given ", syntax error will be printing nonstop...."*/
int handle_args_expand(t_list *line_lst, t_list *env_lst)
{
	while (line_lst)
	{
		if (!(line_lst->next))
		{
			if (((t_input *)line_lst->content)->pipe_sign == 1)
			{
				ft_error_minishell("Syntax error: parse error456.", SYNTAX, 2);
				return (-1);
			}
		}
		// 连续两个node为空，报错newline with prompt
		if (!ft_strncmp(((t_input *)line_lst->content)->temp_line, "", 1)) // handle error: parse error, '| |', '< >', '> <<'
		{
			if (((t_input *)line_lst->content)->pipe_sign == 1)
			{
				if (line_lst->next->next && !ft_strncmp(((t_input *)line_lst->next->content)->temp_line, "", 1)
					&& !ft_strncmp(((t_input *)line_lst->next->next->content)->temp_line, "", 1))
					{
						ft_error_minishell("Syntax error: parse error123.", SYNTAX, 2);
						return (-1);
					}
			}
			else
			{
				if (line_lst->next && !ft_strncmp(((t_input *)line_lst->next->content)->temp_line, "", 1))
					{
						ft_error_minishell("Syntax error: parse error1.", SYNTAX, 2);
						return (-1);
					}
			}
		}
		if (((t_input *)line_lst->content)->quote_type != 1
			 && ft_strchr(((t_input *)line_lst->content)->temp_line, '$'))
			((t_input *)line_lst->content)->temp_line = replace_env_expand(((t_input *)line_lst->content)->temp_line, env_lst);
		line_lst = line_lst->next;
	}
	return (0);
}
