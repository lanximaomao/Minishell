#ifndef BUILDIN_H
# define BUILDIN_H

#include <signal.h>

int		my_cd(char **arg);
int		my_pwd(char **arg);
void	my_env(char **arg);
void	my_export(char **arg);
void	my_unset(char **arg);
int		my_echo(char **arg);
int		check_n(char** arg);

#endif
