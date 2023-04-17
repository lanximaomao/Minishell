#include "minishell.h"

t_list	*segment_split_token(char *segment)
{
	t_list *token;
	char *temp_str; // the string of every token's part
	size_t	i = 0;
	size_t	len = 0;

	while (*segment)
	{
		if (*segment != ' ')
		{
			len = 0;
			while (*segment != ' ' && *segment && ++len)
				segment++;
			token[i++] = ft_substr( - len, 0, len);
		}
		else
			s++;
	}
	token[i] = 0;
	return (token);
}
