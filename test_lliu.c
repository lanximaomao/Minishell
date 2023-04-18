
// #include "minishell.h"
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

void ft_error(char* msg, int error_code)
{
	perror(msg);
	exit(error_code);
}
int main(int argc, char **argv) {

	ft_error("test", -1);
	return 0;
}

// int main(int argc, char **argv) {
// 	char *str = NULL;

// 	str = ft_strdup("test\n");
// 	printf("%s\n", str);
// 	return 0;
// }

