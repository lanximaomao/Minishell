#ifndef PIPE_H
# define PIPE_H

#include "minishell.h"
#include "buidin.h"

char** update_env();
int cmd(char* line);
char* get_path_cmd(char* str);
char **get_path_env();

#endif
