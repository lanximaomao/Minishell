
#include "minishell.h"

typedef struct s_struct
{
	char	*cmd;
}	t_struct;

int main(int argc, char **argv) {
	t_struct *token = NULL;

	token = ft_calloc(sizeof(t_struct), 2);
	token->cmd = ft_strdup("test\n");
	printf("%s\n", token->cmd);
	return 0;
}

// int main(int argc, char **argv) {
// 	char *str = NULL;

// 	str = ft_strdup("test\n");
// 	printf("%s\n", str);
// 	return 0;
// }

