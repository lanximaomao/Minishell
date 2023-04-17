#include "minishell.h"

char	**ft_split_lexer(char const *str)
{
	t_list
	size_t	i;
	size_t	len;

	if (!s)
		return (NULL);
	str_arr = (char **)malloc(sizeof(char *) * (ft_word_count(s, c) + 1));
	if (!str_arr)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s != c && *s && ++len)
				s++;
			str_arr[i++] = ft_substr(s - len, 0, len);
		}
		else
			s++;
	}
	str_arr[i] = 0;
	return (str_arr);
}
