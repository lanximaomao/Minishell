
#include "minishell.h"

int main(void)
// heredoc中“C \ D”的行为和bash不一致
// bash中分别是中断进程130、退出进程131、停止输入等同于正常结束0
// heredoc中位中断<<exitcode1、无反应、输出结束等同于正常结束0
// the subject require in interactive mode: 和在heredoc中一致
// ◦ ctrl-C displays a new prompt on a new line.
// ◦ ctrl-D exits the shell.
// ◦ ctrl-\ does nothing


void shell(void)
{
	char *line;
	char *heredoc;
	line = readline("> ");
	if (line && !ft_strncmp(line, "<<", 3))
	{
		free(line);
		line = NULL;
		while (1)
		{
			heredoc = readline("heredoc>> ");
			if (heredoc && !ft_strncmp(heredoc, "q", 2))
				break;
			free(heredoc);
			heredoc = NULL;
			signal(SIGINT, handle_sig);
		}
	}
	if (line && !ft_strncmp(line, "q", 2))
		exit(0);
	printf("your entered: %s\n", line);
	free(line);
	line = NULL;
	return ;
}

void handle_sig(int sig) {
	if (sig == SIGINT)
	{
		printf("Caught signal %d (SIGINT) ^C \n", sig);
		shell();
	}
	else if (sig == SIGQUIT)
		printf("Caught signal %d (SIGQUIT) ^\\ \n", sig);
	else if (sig == SIGTERM)
	{
		printf("Caught signal %d (SIGTERM) ^D \n", sig);
		exit(0);
	}
}

int main()
{
	char **pp;
	int i = 0;

	while(1)
	{
		// 与bash中的ctrl C行为一致，中断当前进程，返回minishell，记录exitcode = 130
		if (signal(SIGINT, handle_sig) == SIG_ERR) // ctrl C 2
		{
			printf("Error registering SIGINT handler\n");
			exit(1);
		}
		// 与bash中的ctrl \行为一致，退出当前进程，返回minishell，记录exitcode = 131
		// if (sigaction(SIGQUIT, &sa, NULL) == -1) // ctrl \ 3
		// {
		// 	printf("Error registering SIGQUIT handler\n");
		// 	exit(1);
		// }
		// // 输入结束，关闭stdin，返回minishell，记录exitcode = 0
		// if (sigaction(SIGTERM, &sa, NULL) == -1) // ctrl D 15
		// {
		// 	printf("Error registering SIGTERM handler\n");
		// 	exit(1);
		// }
		// shell();
		line = readline("> ");
		if (line && !strncmp(line, "q", 2))
		exit(0);
		// printf("your entered: %s\n", line);
		free(line);
		line = NULL;
	}
	return (0);
} */

void	handle_sig(int sig, siginfo_t *info, void *context)
{
	if (sig == SIGINT)
	{
		// rl_on_new_line(); // 光标移动开头
		rl_replace_line("", 0); // 替换为空字符
		rl_redisplay(); // 重新显示当前命令行，光标移动开头
		(void) sig;
		// printf("Caught signal %d (SIGINT) ^C \n", sig);
		return ;
	}
}
int	main(void)
{
	char	*line;
	struct sigaction sa;

	while (1)
	{
		ft_memset(&sa, 0, sizeof(sa));
		sa.sa_sigaction = handle_sig; // handler function
		sa.sa_flags = SA_SIGINFO; //
		sigemptyset(&sa.sa_mask); // 阻塞其他信号
		// 与bash中的ctrl C行为一致，中断当前进程，返回minishell，记录exitcode = 130
		sigaction(SIGINT, &sa, NULL);
		line = readline("> ");
		if (line && !strncmp(line, "q", 2))
			exit(0);
		free(line);
		line = NULL;
	}
	return 0;

}
