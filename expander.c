#include "minishell.h"

// call this function between lexer and parser
char *handle_expand(t_list *line_lst, t_env *env)
{
	int i = 0;
	int j;
	int k = 0; // 记录遇到$之后，接下来temp_line的起始位置，方便复制substr
	char *tmp_str = NULL;
	char *expand_line = NULL;

	expand_line = (char *)ft_calloc(sizeof(char), 1);
	if (!expand_line)
		return NULL;
	while (line_lst)
	{
		if (((t_input *)line_lst->content)->quote_type == 2)
		{
			while (((t_input *)line_lst->content)->temp_line[i])
			{
				if (((t_input *)line_lst->content)->temp_line[i] == '$')
				{
					j = 0; // iterate through the env_name
					while (env->env_name[j])
					{
						if (ft_strnstr(((t_input *)line_lst->content)->temp_line, env->envname[j], ft_strlen(((t_input *)line_lst->content)->temp_line)))
						{
							tmp_str = ft_strjoin(expand_line, env->env_value[j]);
							if (!tmp_str)
							{
								perror("Malloc error.\n");
								return (NULL);
							}
							free(expand_line);
							expand_line = NULL;
							expand_line = tmp_str;
							i = i + ft_strlen(env->env_name[j]);
							((t_input *)line_lst->content)->temp_line = ft_substr(((t_input *)line_lst->content)->temp_line, i, ft_strlen(((t_input *)line_lst->content)->temp_line));
							break;
						}
					}
				}
				else
				{
					expand_line = (char *)ft_realloc(expand_line, sizeof(char) * (i + 1), sizeof(char) * (i + 2));
					expand_line[i] = ((t_input *)line_lst->content)->temp_line[i];
				}
				i++;
			}
		}

		line_lst = line_lst->next;
	}
		// line_lst->next一次我就需要扩展一次，否则得记录很多expand_sign
	return ;
}
