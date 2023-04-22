
#include "minishell.h"

int main(void)
{
	char **pp;
	int i = 0;

	pp = ft_calloc(sizeof(char *), 101);
	pp[0] = ft_strdup("ls");
	// pp[1] = NULL;
	printf("%s\n", pp[0]);
	printf("%s\n", pp[100]);
	// while (pp[i])
	// {
	// 	printf("%s\n", pp[i++]);
	// }
	return (0);
}
