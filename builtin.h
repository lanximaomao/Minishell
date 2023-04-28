#ifndef builtIN_H
# define builtIN_H

#include "minishell.h"
# include <signal.h>

int is_builtin(t_token* token, t_list *env);
int is_cd(t_token* token, t_list *env);
int		my_cd(char **arg, t_list *env);
int		my_pwd(t_list *env);
void	my_env(t_list *env);
void	my_export(char **arg, t_list *env);
void	my_unset(char **arg, t_list *env);
void	my_exit(char **arg, t_list *env);
void		my_echo(char **arg, t_list *env);
int		check_n(char **arg);
void	my_export_no_aguments(t_list *env);

#endif
