#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf.h"
# include "libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h> // open
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdio.h>  //printf
# include <stdlib.h> // malloc
# include <string.h>
# include <sys/ioctl.h> // ioctl TIOCSTI
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h> // WEXITSTATUS/WIFEXITED/WIFSIGNALED
# include <termios.h>  // tcgetattr tcsetattr ECHOCTL
# include <unistd.h>   // write

# define MALLOC 1
# define FILE_OP 2
# define SYNTAX 3
# define FUNC 4

extern int	g_exitcode;

/*
** redir_sign
** 0 for stdin, 1 for infile "<",
** 2 for heredoc "<<", 3 for outfile ">",
** 4 for append ">>", 5 for errinfile "2<",
** 6 for errheredoc "2<<", 7 for erroutfile "2>",
** 8 for errappend "2>>"
*/
typedef struct s_input
{
	char *temp_line; // cmd_parts, split from readline
	int quote_type;  // 0 for no quote, 1 for single quote, 2 for double quote
	int pipe_sign;   // 0 for no pipe, 1 for left pipe, 2 for right pipe
	int		redir_sign;
}			t_input;

//heredoc, // $
typedef struct s_token
{
	char	*cmd;
	char	**args;
	char	**infile;
	char	**outfile;
	int *output_type; // 0 for stdout, 1 for outfile, 2 for append outfile.
	int cmd_id;       // for heredoc file name
	int		num_args;
	int		num_infile;
	int		num_outfile_type;
	int		fd_in;
	int		fd_out;
}			t_token;

typedef struct s_mini
{
	t_list *env;     // head for env linked list
	t_list *cmd_lst; // head for input arguments linked list
}			t_mini;

// just in case
void		rl_clear_history(void);

// main
int			readline_prompt(t_mini *mini);
void		minishell(t_mini *mini, char *line);
void		ascii_art_pattern(void);
void		exit_with_empty_line(char* msg, int exit_code);
// env_var
char		**env_split(char const *s, char c);
void		env_init(t_mini *mini, char **env);
char		*env_handler(t_list *env, char *str);
char		**env_convert(t_list *env);
int			env_find_and_replace(t_list *env, char *to_find, char *to_replace);

// lexer.c
t_list		*get_linelst(char *line, t_list *line_lst, int i);

// parser.c
t_list		*parse_cmds(t_list *line_lst, t_list *env_lst);

// expander.c
char		*replace_env_expand(char *temp_line, t_list *env_lst);
int			handle_args_expand(t_list *line_lst, t_list *env_lst);
// status is the exitcode of the previous process

// signal.c
void		rl_replace_line(const char *text, int clear_undo);
void	handle_signal(int sig); // signal.c main.c
void		handle_cmd(int sig);
void		handle_signal_heredoc(int sig);
int			event(void);

// mini_utils.c
void		ft_error(char *msg, int error_code, int flag);
int			free_str(char *str);
void		free_char(char **str);
void		free_input(t_input *input);
void		free_tokens(t_token *token, int num_args, int num_infile,
				int num_outfile_type);

#endif
