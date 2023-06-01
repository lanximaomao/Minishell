#include "minishell.h"

// handle $?, use the waitpid() status of process, tips: WEXITSTATUS(), WIFEXITED(), WIFSIGNALED()
char *handle_exitcode(char *str) // test$?-test => test0-test
{
	char *str_status = NULL; // itoa(status)
	char *res = NULL;

	str_status = ft_itoa((unsigned int)g_exitcode); // make sure 0~255
	res = ft_strjoin(str_status, str + 1); // 去掉'?'
	free(str_status);
	str_status = NULL;
	free(str);
	str = NULL;
	return (res);
}

char *replace_env_value(char *tmp_exp, t_list *env_lst, int *sign)
{
	char *tmp_substr;
	int len_envp;

	tmp_substr = NULL;
	len_envp = 0;
	while (env_lst) // iterate the all the env names
	{
		len_envp = ft_strlen(((char **)env_lst->content)[0]);
		if (ft_strnstr(tmp_exp, ((char **)env_lst->content)[0], len_envp)
			 && !ft_isalnum(tmp_exp[len_envp])) // 判断下一个是否是特殊字符（！数字！字母）
		{
			tmp_substr = ft_substr(tmp_exp, len_envp, ft_strlen(tmp_exp));
			if (!tmp_substr)
				ft_error("Malloc failed",  MALLOC, 0);
			free_str(tmp_exp);
			tmp_exp = ft_strjoin(((char **)env_lst->content)[1], tmp_substr);
			if (!tmp_exp)
				ft_error("Malloc failed", MALLOC, 0);
			free_str(tmp_substr);
			*sign = 1; // means replace finished
			break;
		}
		env_lst = env_lst->next;
	}
	return (tmp_exp);
}

// find the env_name and replace it with env_value
char *replace_env(char *tmp_exp, t_list *env_lst) // tmp_substr, 找到环境变量之后，去除env_name的子串
{
	char	*trim_str; // trim_str for "$ABS=dss", output: "=dss"
	int		sign;

	sign = 0;
	tmp_exp = replace_env_value(tmp_exp, env_lst, &sign);
	trim_str = tmp_exp;
	if (sign == 0)
	{
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

char **split_replace(char **tmp_exp, int *i, t_list *env_lst)
{
	char	*tmp_str;// split出来的最后一个字符串，用于连接$

	while (tmp_exp[++(*i)])
	{
		if (tmp_exp[*i][0] == '?')
			tmp_exp[*i] = handle_exitcode(tmp_exp[*i]);
		else if (tmp_exp[*i][0] == ' ')
		{
			tmp_str = tmp_exp[*i]; // 复用
			tmp_exp[*i] = ft_strjoin("$", tmp_str);
			free_str(tmp_str);
		}
		else
			tmp_exp[*i] = replace_env(tmp_exp[*i], env_lst);
	}
	return tmp_exp;
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
		ft_error("Malloc failed", MALLOC, 0);
	while (i < len)
	{
		tmp_join = res;
		if (!(res = ft_strjoin(tmp_join, tmp_exp[i])))
			ft_error("Malloc failed", MALLOC, 0);
		free_str(tmp_join);
		i++;
	}
	return res;
}

