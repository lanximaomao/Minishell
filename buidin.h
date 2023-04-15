#ifndef BUILDIN_H
# define BUILDIN_H

#include <signal.h>
#include "minishell.h"

int		my_cd(char **arg);
int		my_pwd(char **arg);
void	my_env(char **arg, t_list *env);
void	my_export(char **arg, t_list *env);
void	my_unset(char **arg, t_list *env);
int		my_echo(char **arg);
int		check_n(char** arg);

#endif
