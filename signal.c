#include "minishell.h"
#include "signal.h"

void rl_replace_line (const char *, int);

/* ctrl + \ = SIGQUIT, does nothing */

void sa_handle_nothing(int sig)
{
	rl_on_new_line();
	rl_replace_line("  ", 1); // 1 means to clear this line's history
	rl_redisplay();
	return;
}

/* ctrl + D = EOF, exits the shell */
// ! Readline error: interrupted system call.
void sa_handle_ctrl_d(int sig)
{
	return;
}

/* ctrl + c should dispays a new prompt on a new line */
//! by two times ctrl + c we got an readline error
void sa_handle_ctrl_c(int sig)
{
	(void) sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1); // 1 means to clear this line's history
	rl_redisplay();
	return;
}

void signal_handler()
{
	struct sigaction sa_c; //ctrl + c
	struct sigaction sa_d; //ctrl + d
	struct sigaction sa_nothing; //ctrl + \

	sa_c.sa_handler = &sa_handle_ctrl_c;
	sa_d.sa_handler = &sa_handle_ctrl_d;
	sa_nothing.sa_handler = &sa_handle_nothing;

	sigaction(SIGINT, &sa_c, NULL);
	sigaction(SIGUSR1, &sa_d, NULL);
	sigaction(SIGQUIT, &sa_nothing, NULL);
}

void signal_handler_children()
{
	struct sigaction sa_nothing; //ctrl + \

	sa_nothing.sa_handler = &sa_children_exit;
	sigaction(SIGQUIT, &sa_nothing, NULL);
}

/* ctrl + \ = SIGQUIT, quit in children */
void sa_children_exit(int sig)
{
	return;
}

void signal_handler_heredoc()
{
	struct sigaction sa_c; //ctrl + c

	sa_c.sa_handler = &sa_handle_ctrl_c_heredoc;
	sigaction(SIGINT, &sa_c, NULL);
}

void sa_handle_ctrl_c_heredoc()
{
	exit(131) ;
}
