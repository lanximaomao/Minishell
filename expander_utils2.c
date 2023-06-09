#include "minishell.h"

static char *get_tmp_line(char **tmp_exp, char *tmp_line, int i)
{
	if (i == 0)
	{
		tmp_line = ft_strdup("$");
		if (!tmp_line)
			ft_error(" minishell: malloc fail", MALLOC, 0);
	}
	else
		tmp_line = ft_mulstrjoin(tmp_exp, i);
	free_char(tmp_exp);
	return (tmp_line);
}

char	*replace_env_expand(char *tmp_line, t_list *env_lst)
{
	int		i;
	char	**tmp_exp;
	char	*tmp_str;

	i = -1;
	tmp_exp = ft_split(tmp_line, '$');
	if (!tmp_exp)
		ft_error(" minishell: malloc fail", MALLOC, 0);
	if (tmp_line[0] != '$')
		i = 0;
	tmp_exp = split_replace(tmp_exp, &i, env_lst, NULL);
	if (i && tmp_line[ft_strlen(tmp_line) - 1] == '$')
	{
		tmp_str = tmp_exp[i - 1];
		tmp_exp[i - 1] = ft_strjoin(tmp_str, "$");
		if (!tmp_exp[i - 1])
			ft_error(" minishell: malloc fail", MALLOC, 0);
		free_str(tmp_str);
	}
	free_str(tmp_line);
	return (get_tmp_line(tmp_exp, NULL, i));
}
