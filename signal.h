#ifndef SIGNAL_H
# define SIGNAL_H

#include <termios.h>

void signal_main();
void signal_cat();
void signal_in_child();
void signal_heredoc();
void sa_handler_main(int sig);
void sa_handler_cat (int sig);
void sa_handler_in_child(int sig);
void sa_handler_heredoc(int sig);
void prompt();
void	close_echo_control(struct termios *t);
void	open_echo_control(struct termios *t);
void if_received_signal();
void handler_is_receved_signal(int sig);
int ioctl(int fildes, unsigned long request, ...);

#endif
