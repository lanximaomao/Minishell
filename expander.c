#include "minishell.h"

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
static char **exp_each_part(int quote_type, t_input *input, t_list *env_lst, int *i)
{
	int		len;
	int		start;
	char	**tmp_str;
	char	*tmp_str_quote;

	len = 1;
	start = *i;
	tmp_str = (char **)ft_calloc(sizeof(char *), 4);
	if (!tmp_str)
		ft_error(" minishell: malloc fail", MALLOC, 0);
	tmp_str[0] = ft_substr(input->tmp_line, 0, *i);
	if (!tmp_str[0])
		ft_error(" minishell: malloc fail", MALLOC, 0);
	get_i_len(quote_type, i, &len, input->tmp_line);
	tmp_str_quote = ft_substr(input->tmp_line, start, len);
	if (!tmp_str_quote)
		ft_error(" minishell: malloc fail", MALLOC, 0);
	tmp_str[1] = trim_quote(tmp_str_quote, quote_type);
	if (quote_type != 1 && ft_strchr(tmp_str[1], '$'))
		tmp_str[1] = replace_env_expand(tmp_str[1], env_lst);
	tmp_str[2] = ft_substr(input->tmp_line, *i, ft_strlen(input->tmp_line));
	if (!tmp_str[2])
		ft_error(" minishell: malloc fail", MALLOC, 0);
	return (tmp_str);
}

static void	handle_multiquote(t_input *input, t_list *env_lst, int *i, char quote)
{
	int 	quote_type;
	char	**tmp_str;

	quote_type = 0;
	if (quote == '\'')
		quote_type = 1;
	else if (quote == '\"')
		quote_type = 2;
	tmp_str = exp_each_part(quote_type, input, env_lst, i);
	*i = ft_strlen(tmp_str[0]) + ft_strlen(tmp_str[1]) - 1;
	free_str(input->tmp_line);
	input->tmp_line = ft_mulstrjoin(tmp_str, 3);
	free_char(tmp_str);
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
				handle_multiquote(input, env_lst, &i, input->tmp_line[i]);
				if (i == -1)
					break;
			}
		}
		else if (ft_strchr(input->tmp_line, '$'))
		{
			input->tmp_line = replace_env_expand(input->tmp_line, env_lst);
			if (!ft_strncmp(((t_input *)line_lst->content)->tmp_line, "", 1))
				input->ignore_sign = 1;
		}
		line_lst = line_lst->next;
	}
	return ;
}
