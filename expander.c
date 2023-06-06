#include "minishell.h"

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

static char	*trim_quote(char *tmp_line, int quote_type)
{
	char	quote;
	char	*trim_line;
	int		i;
	int		len;

	i = -1;
	len = 0;
	if (quote_type == 1)
		quote = '\'';
	else if (quote_type == 2)
		quote = '\"';
	else
		return (tmp_line);
	trim_line = (char *)malloc(sizeof(char) * (ft_strlen(tmp_line) - 1));
	if (!trim_line)
		ft_error(" minishell: malloc fail", MALLOC, 0);
	while (tmp_line[++i])
	{
		if (tmp_line[i] != quote)
			trim_line[len++] = tmp_line[i];
	}
	free_str(tmp_line);
	trim_line[len] = '\0';
	return (trim_line);
}

static void	get_i_len(int quote_type, int *i, int *len, char *tmp_line)
{
	while ((quote_type == 1 && tmp_line[++(*i)] != '\'')
		|| (quote_type == 2 && tmp_line[++(*i)] != '\"')
		|| (quote_type == 0 && tmp_line[++(*i)]
			&& tmp_line[*i] != '\"' && tmp_line[*i] != '\''))
		(*len)++;
	if (quote_type)
	{
		(*i)++;
		(*len)++;
	}
}

static int	handle_multiquote(t_list *line_lst, t_list *env_lst, int i,
		int quote_type)
{
	int		len;
	int		start;
	t_input	*input;
	char	**tmp_str;

	len = 1;
	start = i;
	input = (t_input *)line_lst->content;
	tmp_str = (char **)ft_calloc(sizeof(char *), 3);
	if (!tmp_str)
		ft_error(" minishell: malloc fail", MALLOC, 0);
	tmp_str[0] = ft_substr(input->tmp_line, 0, i);
	get_i_len(quote_type, &i, &len, input->tmp_line);
	tmp_str[1] = trim_quote(ft_substr(input->tmp_line, start, len), quote_type);
	if (quote_type != 1 && ft_strchr(tmp_str[1], '$'))
		tmp_str[1] = replace_env_expand(tmp_str[1], env_lst);
	tmp_str[2] = ft_substr(input->tmp_line, i, ft_strlen(input->tmp_line));
	i = ft_strlen(tmp_str[0]) + ft_strlen(tmp_str[1]) - 1;
	free_str(input->tmp_line);
	input->tmp_line = ft_mulstrjoin(tmp_str, 3);
	free_char(tmp_str);
	return (i);
}

void	expander_args(t_list *line_lst, t_list *env_lst)
{
	int		i;
	t_input	*input;

	while (line_lst)
	{
		input = (t_input *)line_lst->content;
		i = -1;
		if (input->quote_type)
		{
			while (input->tmp_line[++i])
			{
				if (input->tmp_line[i] == '\"')
					i = handle_multiquote(line_lst, env_lst, i, 2);
				else if (input->tmp_line[i] == '\'')
					i = handle_multiquote(line_lst, env_lst, i, 1);
				else
					i = handle_multiquote(line_lst, env_lst, i, 0);
			}
		}
		else if (ft_strchr(input->tmp_line, '$'))
			input->tmp_line = replace_env_expand(input->tmp_line, env_lst);
		line_lst = line_lst->next;
	}
	return ;
}
