#include "minishell.h"

char	**ft_split_lexer(char *str)
{

	size_t	i = 0;
	size_t	len = 0;

	while (*str)
	{
		if (*str != ' ')
		{
			len = 0;
			while (*str != ' ' && *s && ++len)
				s++;
			str_arr[i++] = ft_substr(s - len, 0, len);
		}
		else
			s++;
	}
	str_arr[i] = 0;
	return (str_arr);
}
