#include "minishell.h"

void handle_quote()
{
	
}

t_list	*segment_split_token(char *segment, int num_quote, int num_dquote)
{
	t_list *token = NULL;
	t_list node;
	char *temp_str; // the string of every token's part
	size_t	i = 0;
	size_t	len = 0;

	while (*segment)
	{
		i = 0;
		if (*segment != ' ')
		{
			len = 0;
			if (*segment == '\"')
			{

			}
			while (*segment != ' ' && *segment && ++len)
				segment++;
			if (!(temp_str = (char *)malloc(sizeof(char) * (len + 1))))
			{
				ft_printf("\033[1;31mError\n\033[0m: %s\n", "Malloc failed\n");
				return (NULL);
			}
			temp_str[i++] = ft_substr(segment - len, 0, len);
			node = ft_lstnew(temp_str);
			if (!token)
			{
				ft_printf("\033[1;31mError\n\033[0m: %s\n", "Malloc failed\n");
				return (NULL);
			}
			if (!token)
				token = node;
			else
				ft_lstadd_back(&token, node);



		}
		else
			segment++;
	}
	token[i] = 0;
	return (token);
}
