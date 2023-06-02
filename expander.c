#include "minishell.h"

char	*replace_env_expand(char *tmp_line, t_list *env_lst)
{
	int		i;
	char	**tmp_exp;
	char	*tmp_str;

	i = -1;
	tmp_exp = ft_split(tmp_line, '$');
	if (!tmp_exp)
		ft_error("Malloc failed", MALLOC, 0);
	if (tmp_line[0] != '$')
		i = 0;
	tmp_exp = split_replace(tmp_exp, &i, env_lst);
	if (i && tmp_line[ft_strlen(tmp_line) - 1] == '$')
	{
		tmp_str = tmp_exp[i - 1];
		tmp_exp[i - 1] = ft_strjoin(tmp_str, "$");
		free_str(tmp_str);
	}
	free_str(tmp_line);
	if (i == 0)
		tmp_line = ft_strdup("$");
	else
		tmp_line = ft_mulstrjoin(tmp_exp, i);
	free_char(tmp_exp);
	return (tmp_line);
}

void	expander_args(t_list *line_lst, t_list *env_lst)
{
	t_input	*input;

	while (line_lst)
	{
		input = (t_input *)line_lst->content;
		if (input->quote_type != 1 && ft_strchr(input->tmp_line, '$'))
			input->tmp_line = replace_env_expand(input->tmp_line, env_lst);
		line_lst = line_lst->next;
	}
	return ;
}
