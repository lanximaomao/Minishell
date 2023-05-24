#include "minishell.h"
#include "signal.h"

void rl_replace_line (const char *, int);
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);

/* ctrl + c = SIGINT, 2 */
/* ctrl + \ = SIGQUIT, 3 */
/* ctrl + D = EOF */

void signal_main()
{
	struct sigaction sa;

	sa.sa_handler = &sa_handler_main;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void signal_cat()
{
	struct sigaction sa;

	sa.sa_handler =  &sa_handler_cat;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void signal_in_child()
{
	struct sigaction sa;

	sa.sa_handler =  &sa_handler_in_child;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void signal_heredoc()
{
	struct sigaction sa;

	sa.sa_handler = &sa_handler_heredoc;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void sa_handler_main(int sig)
{
	//printf("calling from sa_handler main\n");
	if (sig == SIGINT && g_exitcode == 256)
		g_exitcode = 258;
	if (sig == SIGINT && g_exitcode != 258)
	{
		g_exitcode = 1;
		printf("\n");
	}
	//else if (g_exitcode == -1)
	//	g_exitcode = 1;
	//printf("g_exitcode=%d\n", g_exitcode);
	prompt();
}

//// why these exitcode got reset somewhere, but where?
void sa_handler_cat (int sig)
{
	if (sig == SIGINT)
		printf("\n");//
	if (sig == SIGQUIT)
		printf("Quit: 3\n");
	//printf("am I here?\n");
	g_exitcode = sig + 128;
	//signal(SIGINT, SIG_IGN);//to ingnore the sigint, otherwise minishell prompt will be printed two times
}

void sa_handler_in_child(int sig)
{
	exit(g_exitcode);
}


// why do we have two extra newlines if "<< f1 cat"?
void sa_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		//printf("heredoc got a ctrl+c signal\n");
		g_exitcode = 513;// trigger the exit of the heredoc loop
		ioctl(STDIN_FILENO, TIOCSTI, "\x04");//inject a newline into stdin buffer
		//printf("exitcode00=%d\n", g_exitcode);
	}
}

void prompt()
{
	rl_on_new_line();
	rl_replace_line("", 1); // 1 means to clear this line's history
	rl_redisplay();
}

void	close_echo_control(struct termios *t)
{
	t->c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, TCSANOW, t))
		ft_error(" error in tcsetattr", 1);
}

void	open_echo_control(struct termios *t)
{
	t->c_lflag |= ECHOCTL;
	if (tcsetattr(0, TCSANOW, t) == -1)
		ft_error(" error in tcsetattr", 1);
}


void if_received_signal()
{
	struct sigaction sa;

	sa.sa_handler = &handler_is_receved_signal;
	sigaction(SIGINT, &sa, NULL);
}

void handler_is_receved_signal(int sig)
{
	if (sig == SIGINT)
		g_exitcode = 1;
}
