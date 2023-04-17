#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf.h"
# include "get_next_line_bonus.h"
# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>


enum e_quote_type
{
	EMPTY,
	CMD,
	ARG,
	INRDC,		// "<"
	HEREDOC,	// "<<"
	OUTRDC,		// ">>"
	APPEND,		// "<<"
	PIPE,		// "|"
	DOLLOR		// "$"

}	t_quote_type;

typedef struct s_env
{
	char	*env_name;
	char	*env_value;
}			t_env;

typedef struct s_input
{
	char	**cmd_segments;
	t_list	**cmd_tokens;
	char	**cmd_tokens_q;
	char	*temp_line;
	int 	quote_type;

}			t_input;

typedef struct s_token
{
	char	*cmd;
	char	**infile;
	char	**outfile;

	char	*heredoc;
	int		sign_in;
	int		sign_out; // 0 for stdout, 1 for outfile, 2 for append outfile.
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
