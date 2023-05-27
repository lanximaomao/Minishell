#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

//builtin
int		is_builtin(t_token *token, t_list *env);
int		run_builtin(t_token *token, t_list **env);
int		is_equal_sign(char *arg, int i);
int		printf_error(char *msg, int code);

//functions
int		my_env(t_list *env);
void	my_exit(char **arg);
void	my_pwd(t_list *env);
void	my_cd(char **arg, t_list *env);
void	my_echo(char **arg, t_list *env);
void	my_export(char **arg, t_list *env);
void	my_unset(char **arg, t_list **env);

#endif
