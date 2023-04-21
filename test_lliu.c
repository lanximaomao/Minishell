
#include "minishell.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h> // malloc
#include <stdio.h> //printf
#include <unistd.h> // write
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> // open
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <dirent.h>

void handle_exitcode(int status, char *str) // test$?-test => test0-test
{
	char *str_status = NULL; // itoa(status)
	char *res = NULL;

	str_status = ft_itoa(status);
	res = ft_strjoin(str_status, str + 1); // 去掉'?'
	free(str_status);
	str_status = NULL;
	free(str);
	str = NULL;
	str = res;
	// return (res);
}

int main(int argc, char **argv) {

	char *str = NULL;

	str = ft_strdup("");
	ft_strncmp(str, "exit", 4);
	printf("%zu\n", ft_strlen(str));
}


/* int main(int argc, char **argv) {

	char *res = NULL;
	char *tmp = NULL;

	char **tmp_exp = ft_split("test$test$HOME", '$');
	tmp_exp[1] = "\0";
	int i = 1;
	while(i < 3)
	{
		if (!res)
			res = ft_strdup(tmp_exp[0]);
		res = ft_strjoin(res, tmp_exp[i]);
		// printf("%s\n", res);
		i++;
	}
	printf("%s\n", res);
} */

// int main(int argc, char **argv) {
// 	char *str = NULL;

// 	str = ft_strdup("test\n");
// 	printf("%s\n", str);
// 	return 0;
// }

