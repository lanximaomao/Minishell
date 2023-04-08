#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include "libft/ft_printf.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

typedef struct s_env
{
	char* env_name;
	char* env_value;
}t_env;

typedef struct s_input
{
	char* cmd;
	char** arg;
	int fd_in;
	int fd_out;
	int sign_in;
	int sign_out;
} t_input;

typedef struct s_mini
{
	t_env *env;
	t_input* input;
} t_mini;

void error(char* msg, int error_code);

#endif
