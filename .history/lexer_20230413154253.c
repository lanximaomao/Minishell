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
			if (!(temp_str = (char *)malloc(sizeof(char) * (len + 1))))
			{
				return (NULL);
			}
				ft_printf("\033[1;31mError\n\033[0m: %s\n", "Malloc failed\n");
			temp_str[i++] = ft_substr(segment - len, 0, len);

		}
		else
			segment++;
	}
	token[i] = 0;
	return (token);
}
