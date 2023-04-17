#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf.h"
# include "get_next_line_bonus.h"
# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>

# define CMD 1
# define ARG 2
# define INRDC 3 	// "<"
# define HEREDOC 4 	// "<<"
# define OUTRDC 5 	// ">>"
# define APPEND 6	// "<<"
# define PIPE 8	// "|"
# define PIPE 7	// "|"



typedef struct s_env
{
	char	*env_name;
	char	*env_value;
}			t_env;

typedef struct s_input
{
	char	**cmd_segment;
	char	**cmd_tokens_;
	char	**cmd_tokens_quote;
	char	**cmd_tokens_dq;

	int 	token_type;


	char	*cmd;
	int		fd_in;
	char	**infile;
	int		fd_out;
	char	**outfile;
	int		sign_in;
	int		sign_out;
}			t_input;


typedef struct s_mini
{
	t_list *env;   // head for env linked list
	t_list *cmd_input; // head for input arguments linked list
}			t_mini;


// mini_utils.c
void		error(char *msg, int error_code);
int			env_init(t_mini *mini, char **env);

// parsor.c
void		parser(char *line);

// minishell.c
void		minishell(char *line);



#endif
