#ifndef SIGNAL_H
# define SIGNAL_H

#include <termios.h>

void signal_main();
void signal_children();
void signal_heredoc();
void sa_handler_main(int sig);
void sa_handler_children (int sig);
void sa_handler_heredoc(int sig);
void prompt();


#endif
