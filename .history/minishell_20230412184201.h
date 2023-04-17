#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf.h"
# include "get_next_line_bonus.h"
# include "libft.h"
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
	t_list	*input_cmd;
	t_list	*input_arg;
}			t_input;
// the cmd linked list
typedef struct s_cmd
{
	char	*cmd;
	char	**arg;
	int		fd_in;
	int		fd_out;
	int		sign_in;
	int		sign_out;

}			t_cmd;

typedef struct s_mini
{
	t_list *env;   // head for env linked list
	t_list *input; // head for input arguments linked list
}			t_mini;


// mini_utils.c
void		error(char *msg, int error_code);
int			env_init(t_mini *mini, char **env);

// parsor.c
void		parser(char *line);

// minishell.c
void		minishell(char *line);



#endif
