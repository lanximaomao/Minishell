#include "minishell.h"
#include "signal.h"

void rl_replace_line (const char *, int);
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);

/* ctrl + c = SIGINT */
/* ctrl + \ = SIGQUIT */
/* ctrl + D = EOF */

void signal_main()
{
	struct sigaction sa;

	sa.sa_handler = &sa_handler_main;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void signal_children()
{
	struct sigaction sa;

	sa.sa_handler =  &sa_handler_children;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void signal_heredoc()
{
	struct sigaction sa;

	sa.sa_handler = &sa_handler_heredoc;
	sigaction(SIGINT, &sa, NULL);
}

void sa_handler_main(int sig)
{
	if (sig == SIGINT)
	{
		g_exitcode = 1;
		write(1, "\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		int fd;
		struct termios term;

		//printf("sig=%d\n", sig);
		fd = 0;
		if (tcgetattr(fd, &term) != -1)
		{
			//term.c_iflag &= ~(IXON);
			//term.c_lflag &= ~(ECHO);
			tcsetattr(fd, TCSANOW, &term);
		}
	}
	prompt();
	return;
}

void sa_handler_children (int sig)
{
	if (sig == SIGINT)
		g_exitcode = 130;
	else if (sig == SIGQUIT)
		g_exitcode = 131;
}

void sa_handler_heredoc(int sig)
{
	if (sig == SIGINT)
		g_exitcode = 256;// trigger the exit of the heredoc loop
	write(1, "\n", 1);
	prompt();
	return;
}

void prompt()
{
	rl_on_new_line();
	rl_replace_line("", 1); // 1 means to clear this line's history
	rl_redisplay();
}
