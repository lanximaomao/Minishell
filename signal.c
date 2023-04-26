#include "minishell.h"
#include "signal.h"


/* ctrl + \ = SIGQUIT, does nothing */
//! by two times ctrl + \ we got an readline error
void sa_handel_nothing(int sig)
{
	//printf("I am calling CTRL + \\");
	//fflush(stdout);
	return;
}

/* ctrl + D = EOF, exits the shell */
// ! Readline error: interrupted system call.
void sa_handel_ctrl_d(int sig)
{
	exit(1);
}

/* ctrl + c should dispays a new prompt on a new line */
//! by two times ctrl + c we got an readline error
void sa_handel_ctrl_c(int sig)
{
	printf("I am calling CTRL + C");
	(void) sig;
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
	return;
}

void signal_handler()
{
	struct sigaction sa_c; //ctrl + c
	struct sigaction sa_d; //ctrl + d
	struct sigaction sa_nothing; //ctrl + \

	sa_c.sa_handler = &sa_handel_ctrl_c;
	sa_d.sa_handler = &sa_handel_ctrl_d;
	sa_nothing.sa_handler = &sa_handel_nothing;
	sigaction(SIGINT, &sa_c, NULL);
	sigaction(SIGUSR1, &sa_d, NULL);
	sigaction(SIGQUIT, &sa_nothing, NULL);
}

