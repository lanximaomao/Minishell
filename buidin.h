#ifndef BUILDIN_H
# define BUILDIN_H

#include <signal.h>

int is_buildin(char** cmd_args, t_list *env);

int		my_cd(char **arg, t_list *env);
int		my_pwd(t_list *env);
void	my_env(t_list *env);
void	my_export(char **arg, t_list *env);
void	my_unset(char **arg, t_list *env);
void	my_exit(int status);

int		my_echo(char **arg, t_list *env);
int		check_n(char** arg);
void my_export_no_aguments(t_list *env);

#endif
