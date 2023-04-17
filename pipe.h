#ifndef PIPE_H
# define PIPE_H

#include "minishell.h"
#include "buidin.h"

int cmd(t_mini *mini, char* line);
char* get_path_cmd(char* str, t_list *env);
char **get_path_env(t_list *env);



#endif
