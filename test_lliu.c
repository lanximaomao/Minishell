
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


int main(int argc, char **argv) {

	char *res = NULL;
	char *tmp = NULL;

	char **tmp_exp = ft_split("test$TES$HOME", '$');
	res = ft_strdup("");
	free(tmp_exp[1]);
	tmp_exp[1] = NULL;
	tmp_exp[1] = ft_strdup("");
	int i = 0;
	while(i < 3)
	{
		tmp = res;
		res = ft_strjoin(tmp, tmp_exp[i]);
		free(tmp);
		tmp = NULL;
		i++;
	}
	free_char(tmp_exp);
	printf("%s\n", res);
	free(res);
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

