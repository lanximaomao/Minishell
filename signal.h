#ifndef SIGNAL_H
# define SIGNAL_H

void signal_handler();
void signal_handler_children();
void sa_handle_ctrl_c(int sig);
void sa_handle_ctrl_d(int sig);
void sa_handle_nothing(int sig);
void sa_children_exit(int sig);


#endif
