#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft_42/inc/ft_printf.h"
# include "libft_42/inc/get_next_line_bonus.h"
# include "libft_42/inc/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>

typedef struct s_env
{
	char	*env_name;
	char	*env_value;
}			t_env;

typedef struct s_input
{
	char	*cmd;
	char	**arg;
	int		fd_in;
	int		fd_out;
	int		sign_in;
	int		sign_out;
}			t_input;

typedef struct s_mini
{
	t_list *env;   // head for env linked list
	t_list *input; //head for input arguments linked list
}			t_mini;

t_mini *mini;

void		error(char *msg, int error_code);
void		minishell(t_mini *mini, char *line);
int			env_init(t_mini *mini, char **env);
char**		env_convert(t_list* env);
char*		env_handler(t_list *env, char* str);

#endif
