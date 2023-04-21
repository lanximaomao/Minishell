
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


void handle_sig(int sig) {
	if (sig == SIGINT)
	{
		printf("Caught signal %d (SIGINT) ctrl C \n", sig);
		exit(0);
	}
	else if (sig == SIGQUIT)
	{
		printf("Caught signal %d (SIGQUIT) ctrl \\ \n", sig);
		exit(0);
	}
	else if (sig == SIGTERM)
	{
		printf("test\n");
		printf("Caught signal %d (SIGTERM) ctrl D \n", sig);
		exit(0);
	}
}
int main()
{
	char buffer[256];

	// if (signal(SIGINT, handle_sig) == SIG_ERR) // ctrl C 2
	// {
	// 	printf("Error registering SIGINT handler\n");
	// 	exit(1);
	// }
	// if (signal(SIGQUIT, handle_sig) == SIG_ERR) // ctrl \ 3
	// {
	// 	printf("Error registering SIGQUIT handler\n");
	// 	exit(1);
	// }
	// if (signal(SIGTERM, sigterm_handler) == SIG_ERR) // ctrl D 15
	// {
	// 	printf("Error registering SIGTERM handler\n");
	// 	exit(1);
	// }
	while (fgets(buffer, 256, stdin)) {
		printf("You entered: %s", buffer);
	}
	signal(SIGINT, handle_sig);
	printf("%d\n", SIGTERM);

	return 0;
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

