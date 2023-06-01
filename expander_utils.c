#include "minishell.h"

/*
** test$?-test => test0-test
*/
char	*handle_exitcode(char *str)
{
	char	*str_status;
	char	*res;

	str_status = NULL;
	res = NULL;
	str_status = ft_itoa((unsigned int)g_exitcode);
	res = ft_strjoin(str_status, str + 1);
	free(str_status);
	str_status = NULL;
	free(str);
	str = NULL;
	return (res);
}

char	*replace_env_value(char *tmp_exp, t_list *env_lst, int *sign)
{
	char	*tmp_substr;
	int		len_envp;

	tmp_substr = NULL;
	len_envp = 0;
	while (env_lst)
	{
		len_envp = ft_strlen(((char **)env_lst->content)[0]);
		if (ft_strnstr(tmp_exp, ((char **)env_lst->content)[0], len_envp)
			&& !ft_isalnum(tmp_exp[len_envp]))
		{
			tmp_substr = ft_substr(tmp_exp, len_envp, ft_strlen(tmp_exp));
			if (!tmp_substr)
				ft_error("Malloc failed", MALLOC, 0);
			free_str(tmp_exp);
			tmp_exp = ft_strjoin(((char **)env_lst->content)[1], tmp_substr);
			if (!tmp_exp)
				ft_error("Malloc failed", MALLOC, 0);
			free_str(tmp_substr);
			*sign = 1;
			break ;
		}
		env_lst = env_lst->next;
	}
	return (tmp_exp);
}

/*
** find the env_name and replace it with env_value
** trim_str for "$ABS=dss", output: "=dss"
*/
char	*replace_env(char *tmp_exp, t_list *env_lst)
{
	char	*trim_str;
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
				break ;
			}
			tmp_exp++;
		}
	}
	return (tmp_exp);
}

char	**split_replace(char **tmp_exp, int *i, t_list *env_lst)
{
	char	*tmp_str;

	while (tmp_exp[++(*i)])
	{
		if (tmp_exp[*i][0] == '?')
			tmp_exp[*i] = handle_exitcode(tmp_exp[*i]);
		else if (tmp_exp[*i][0] == ' ')
		{
			tmp_str = tmp_exp[*i];
			tmp_exp[*i] = ft_strjoin("$", tmp_str);
			free_str(tmp_str);
		}
		else
			tmp_exp[*i] = replace_env(tmp_exp[*i], env_lst);
	}
	return (tmp_exp);
}

/*
** len is the length of tmp_exp
*/
char	*ft_mulstrjoin(char **tmp_exp, int len)
{
	int		i;
	char	*tmp_join;
	char	*res;

	i = 0;
	tmp_join = NULL;
	res = NULL;
	res = ft_strdup("");
	if (!res)
		ft_error("Malloc failed", MALLOC, 0);
	while (i < len)
	{
		tmp_join = res;
		res = ft_strjoin(tmp_join, tmp_exp[i]);
		if (!res)
			ft_error("Malloc failed", MALLOC, 0);
		free_str(tmp_join);
		i++;
	}
	return (res);
}
