#include "minishell.h"
// minishell
void handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		if (g_exitcode == 256 || g_exitcode == 386)
			g_exitcode = 386; // 255 + 1 + 130
		else
		{
			printf("\n");
			g_exitcode = 1;
		}
		rl_on_new_line(); // readline移动到新行，保留输入，否则会直接清空当前输入
		rl_replace_line("", 0); // 替换为空字符，需要在display之前
		rl_redisplay(); // 重新显示当前命令行prompt + replace_line函数所替换的rl_line_buffer
		(void) sig;
		return ;
	}
}
// cmd cat grep wc...
void handle_cmd(int sig)
{
	if (sig == SIGINT)
	{
		//g_exitcode = 130;
		printf("\n");
		(void) sig;
	}
	else if (sig == SIGQUIT) // parent process ignore and quit in child process
	{
		printf("^\\Quit: %d\n", sig);
		//g_exitcode = 131;
	}
	return ;
	// exit(g_exitcode);
	// 这里不能使用exit，在main.c中minishell（）进行signal注册后，调用exe；
	// exe中fork了一个子进程来运行cmd；
	// 比如，运行cat时候进行^C中断，父子进程均收到信号需要分别处理，如果exit，子进程退出后，父进程也会退出；
}

void handle_signal_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		// ioctl(0, TIOCSTI, "\x04"); // heredoc结束，自动添加ctrl D EOF。
		// 不能使用的原因是，如果EOF了之后行为会与heredoc的^D时一致，导致无法换行。
		// heredoc中，ctrl+d新的prompt不换行，而ctrl+c新的prompt换行
		ioctl(0, TIOCSTI, "\n"); // heredoc结束，自动添加"\n"
		printf("\033[1A"); // 光标上移一行
		g_exitcode = -2;
	}
	else
		g_exitcode = sig;
	rl_replace_line("", 0); // 替换为空字符，需要在display之前
	rl_redisplay(); // 重新显示当前命令行prompt + replace_line函数所替换的rl_line_buffer
	// rl_done = 1; // 需要和hook搭配使用
	return ;
}

