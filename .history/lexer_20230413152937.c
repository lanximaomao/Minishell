#include "minishell.h"

t_list	**ft_split_lexer(char *str)
{
	t_list 
	size_t	i = 0;
	size_t	len = 0;

	while (*str)
	{
		if (*str != ' ')
		{
			len = 0;
			while (*str != ' ' && *str && ++len)
				str++;
			str_arr[i++] = ft_substr(s - len, 0, len);
		}
		else
			s++;
	}
	str_arr[i] = 0;
	return (str_arr);
}
