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
# define PIPE 8	// "$"



typedef struct s_env
{
	char	*env_name;
	char	*env_value;
}			t_env;
// lliu

typedef struct s_minilist
{
	void			*content;
	struct s_list	*next;
}					t_minilist;

typedef struct s_input
{
	char	**cmd_segments;
	t_list	**cmd_tokens;
	char	**cmd_tokens_q;
	char	**cmd_tokens_dq;

	int 	token_type;

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
