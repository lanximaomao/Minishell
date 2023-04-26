#ifndef SIGNAL_H
# define SIGNAL_H

void signal_handler();
void sa_handel_ctrl_c(int sig);
void sa_handel_ctrl_d(int sig);
void sa_handel_nothing(int sig);


#endif
