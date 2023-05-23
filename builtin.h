#ifndef builtIN_H
# define builtIN_H

#include "minishell.h"
# include <signal.h>

int buildtin_run(t_token* token, t_list **env);
void		my_cd(char **arg, t_list *env);
void		my_pwd(t_list *env);
int	my_env(char** arg, t_list *env);
void	my_export(char **arg, t_list *env);
void	my_unset(char **arg, t_list **env);
void	my_exit(char **arg, t_list *env);
void		my_echo(char **arg, t_list *env);

#endif
