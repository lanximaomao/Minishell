#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line_bonus.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h> // malloc
#include <stdio.h> //printf
#include <unistd.h> // write
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> // open
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <dirent.h>

// exit(error_code)
# define MALLOC 1
# define FILE_OP 2
# define SYNTAX 3
# define FUNC 4

/*
 1. Malloc failed.
 2. File operation failed. // open, read, close, write
 4. Syntax error. *****.
 3. Readline error.
 5. Chdir error.
 6. Fork erroe.
 7. Pipe error.
 8. Getcwd error.

*/


typedef struct s_input
{
	char	*temp_line; // cmd_parts, split from readline
	int 	quote_type; // 0 for no quote, 1 for single quote, 2 for double quote
	// token types
	int 	pipe_sign; // 0 for no pipe, 1 for left pipe, 2 for right pipe
	int		redir_sign; // 0 for stdin, 1 for infile "<", 2 for heredoc "<<", 3 for outfile ">", 4 for append ">>"
						// 5 for errinfile "2<", 6 for errheredoc "2<<", 7 for erroutfile "2>", 8 for errappend "2>>"
}			t_input;

typedef struct s_token
{
	char	*cmd;
	char	**args;
	char	**infile;
	char	**outfile;
	// char	**errfile;
	int		*output_type; // 0 for stdout, 1 for outfile, 2 for append outfile.
	int		num_args;
	int		num_infile;
	int		num_outfile_type;
	// int		num_errfile;

}			t_token;


typedef struct s_mini
{
	t_list *env;   // head for env linked list
	t_list *cmd_lst; // head for input arguments linked list
}			t_mini;

// mini_utils.c
void ft_error(char* msg, int error_code);
void free_char(char **str);
void free_input(t_input *input);
void free_tokens(t_token *token, int num_args, int num_infile, int num_outfile_type);

// lexer.c
t_list *get_linelst(char *line);


void		minishell(t_mini *mini, char *line);
int			env_init(t_mini *mini, char **env);
char**		env_convert(t_list* env);
char*		env_handler(t_list *env, char* str);

// parser.c
t_list *parse_cmds(t_list *line_lst);


// minishell.c





#endif
