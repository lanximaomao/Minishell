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
# define PIPE 7	// "|"



typedef struct s_env
{
	char	*env_name;
	char	*env_value;
}			t_env;

typedef struct s_input
{
	char	*temp_line; // cmd_parts, split from readline
	int 	quote_type; // 0 for no quote, 1 for single quote, 2 for double quote
	int 	pipe_sign; // 0 for no pipe, 1 for left pipe, 2 for right pipe
	int		redir_sign; // 0 for stdin, 1 for infile "<", 2 for heredoc "<<", 3 for outfile ">", 4 for append ">>"
	, 5 for errinput, 6 for erroutput
}			t_input;

typedef struct s_token
{
	char	*cmd;
	char	**infile;
	char	**outfile;
	int		output_type; // 0 for stdout, 1 for outfile, 2 for append outfile.

	char	*heredoc;
	int		sign_in;
}			t_token;


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
