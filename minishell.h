#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "ft_printf.h"
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
# include <readline/readline.h>
# include <readline/history.h>

// exit(error_code)
# define MALLOC 1
# define FILE_OP 2
# define SYNTAX 3
# define FUNC 4

extern int g_exitcode;

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
	int		fd_in; // add by Lin
	int		fd_out; // add by Lin
	// int		num_errfile;

}			t_token;


typedef struct s_mini
{
	t_list *env;   // head for env linked list
	t_list *cmd_lst; // head for input arguments linked list
}			t_mini;

// mini_utils.c
void ft_error(char* msg, int error_code);
void ft_error_minishell(char* msg, int error_code, int sig);
int free_str(char *str);
void free_char(char **str);
void free_input(t_input *input);
void free_tokens(t_token *token, int num_args, int num_infile, int num_outfile_type);

// lexer.c
t_list *get_linelst(char *line, t_list *line_lst, int i);


void		minishell(t_mini *mini, char *line, int exitcode);
int			env_init(t_mini *mini, char **env);
char**		env_convert(t_list* env);
char*		env_handler(t_list *env, char* str);

// parser.c
t_list *parse_cmds(t_list *line_lst, t_list *env_lst, int exitcode);

// expander.c
char *replace_env_expand(char *temp_line, t_list *env_lst);
void handle_args_expand(t_list *line_lst, t_list *env_lst); // status is the exitcode of the previous process

int env_find_and_replace(t_list *env, char* to_find, char* to_replace);
void test_env_functions(t_mini *mini);
// minishell.c


// executor.c
int executor_single(t_mini *mini);
int executor(t_mini *mini, int size);


// test_lliu.c
void shell(void);
void handle_sig(int sig);

#endif
