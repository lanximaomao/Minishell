
#include "minishell.h"

static int handle_parse_error(t_list *line_lst, int sign)
{
	// the | or < is the last character
	if (sign == 1 && (((t_input *)line_lst->content)->pipe_sign == 1
		|| ((t_input *)line_lst->content)->redir_sign != 0))
	{
		ft_error("Syntax error: parse error", SYNTAX, 1);
		return (-1);
	}
	// 当前是pipe则需要考虑下一个和下下个是否连续为空
	else if (sign == 2 && line_lst->next->next
		&& !ft_strncmp(((t_input *)line_lst->next->content)->temp_line, "", 1)
		&& !ft_strncmp(((t_input *)line_lst->next->next->content)->temp_line, "", 1))
	{
		ft_error("Syntax error: parse error", SYNTAX, 1);
		return (-1);
	}
	// 当前不是pipe，只需要考虑这个和下一个是否连续为空
	else if (sign == 3 && line_lst->next
		&& !ft_strncmp(((t_input *)line_lst->next->content)->temp_line, "", 1))
	{
		ft_error("Syntax error: parse error", SYNTAX, 1);
		return (-1);
	}
	return (0);
}

// split, replace, joint, return
// for reuse this function in heredoc
char *replace_env_expand(char *temp_line, t_list *env_lst)
{
	int i;
	char **tmp_exp; // $ split每个temp_line
	char *tmp_str;

	i = -1;
	tmp_exp = ft_split(temp_line, '$');
	if (!tmp_exp)
		ft_error("Malloc failed", MALLOC, 0);
	if (temp_line[0] != '$')
		i = 0; // the first arg no need to handle
	tmp_exp = split_replace(tmp_exp, &i, env_lst);
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

int expander_args(t_list *line_lst, t_list *env_lst)
{
	t_input		*input;

	while (line_lst)
	{
		input = (t_input *)line_lst->content;
		if (!(line_lst->next))
			if (handle_parse_error(line_lst, 1) == -1)
				return (-1);
		// 连续两个node为空，报错newline with prompt
		if (!ft_strncmp(input->temp_line, "", 1))
		{
			if (input->pipe_sign == 1)
			{
				if (handle_parse_error(line_lst, 2) == -1)
					return (-1);
			}
			else
				if (handle_parse_error(line_lst, 3))
					return (-1);
		}
		if (input->quote_type != 1 && ft_strchr(input->temp_line, '$'))
			input->temp_line = replace_env_expand(input->temp_line, env_lst);
		line_lst = line_lst->next;
	}
	return (0);
}
