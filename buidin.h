#ifndef BUILDIN_H
# define BUILDIN_H

#include <signal.h>

int		cd(char **arg);
int		pwd(char **arg);
void	print_env(char **arg);
void	export(char **arg);
void	unset(char **arg);

#endif
