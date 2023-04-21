
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

// heredoc中“C \ D”的行为和bash不一致
// bash中分别是中断进程130、退出进程131、停止输入等同于正常结束0
// heredoc中位中断<<exitcode1、无反应、输出结束等同于正常结束0

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

	// 与bash中的ctrl C行为一致，中断当前进程，返回minishell，记录exitcode = 130
	if (signal(SIGINT, handle_sig) == SIG_ERR) // ctrl C 2
	{
		printf("Error registering SIGINT handler\n");
		exit(1);
	}
	// 与bash中的ctrl \行为一致，退出当前进程，返回minishell，记录exitcode = 131
	if (signal(SIGQUIT, handle_sig) == SIG_ERR) // ctrl \ 3
	{
		printf("Error registering SIGQUIT handler\n");
		exit(1);
	}
	// 输入结束，关闭stdin，返回minishell，记录exitcode = 0
	if (signal(SIGTERM, handle_sig) == SIG_ERR) // ctrl D 15
	{
		printf("Error registering SIGTERM handler\n");
		exit(1);
	}
	while(1)
	{
		readline("> ");
	}
	// while (fgets(buffer, 256, stdin)) {
	// 	printf("You entered: %s", buffer);
	// }
	// signal(SIGINT, handle_sig);
	// printf("%d\n", SIGTERM);

	return 0;
}

