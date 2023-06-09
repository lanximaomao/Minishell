#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft_42/inc/ft_printf.h"
# include "libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>

# define FILE_OP 1
# define MALLOC 2
# define SYNTAX 3
# define FUNC 4

extern int	g_exitcode;

/*
** quote_type: 0 for no quote, 1 for single quote, 2 for double quote
** pipe_sign:  0 for no pipe, 1 for left pipe, 2 for right pipe
** 0 for stdin, 1 for infile "<", 2 for heredoc "<<", 3 for outfile ">",
** 4 for append ">>"
*/
typedef struct s_input
{
	char	*tmp_line;
	int		quote_type;
	int		pipe_sign;
	int		redir_sign;
	int		ignore_sign; // 0 for no ignore, 1 for ignore
}			t_input;

/*
** file_type: 1 for outfile, 2 for append outfile, 3 for infile
*/
typedef struct s_token
{
	char	*cmd;
	char	**args;
	char	**file_redir;
	int		*file_type;
	int		cmd_id;
	int		num_infile;
	int		num_outfile;
	int		num_args;
	int		fd_in;
	int		fd_out;
}			t_token;

typedef struct s_mini
{
	t_list	*env;
	t_list	*cmd_lst;
}			t_mini;

/* just in case */
void		rl_clear_history(void);
void		rl_replace_line(const char *text, int clear_undo);

/* main */
int			readline_prompt(t_mini *mini);
void		minishell(t_mini *mini, char *line);
void		ascii_art_pattern(void);
void		exit_with_empty_line(char *msg, int exit_code);
void		remove_tmp_file(int size);

/* env_var */
void		env_init(t_mini *mini, char **env);
char		**env_split(char const *s, char c);
char		*env_handler(t_list **env, char *str);
char		**env_convert(t_list **env);
int			env_find_and_replace(t_list **env, char *to_find, char *to_replace, int sign);

/* lexer */
t_list		*lexer_get_linelst(char *line, t_list *line_lst, int i);

/* validator.c */
void		ft_error(char *msg, int error_code, int flag);
int			validator(t_list **line_lst);

/* expander.c */
void		expander_args(t_list *line_lst, t_list *env_lst);

/* expander_utils.c */
char		*handle_exitcode(char *str);
char		*replace_env_value(char *tmp_exp, t_list *env_lst, int *sign);
char		*replace_env(char *tmp_exp, t_list *env_lst);
char		*ft_mulstrjoin(char **tmp_exp, int len);
char		**split_replace(char **tmp_exp, int *i, t_list *env_lst, char *tmp_str);
/* expander_utils2.c */
char		*replace_env_expand(char *tmp_line, t_list *env_lst);

/* parser.c */
t_list		*parser_cmds(t_list *line_lst, t_list *env_lst);

/* parser_utils.c */
void		create_lst(t_list **lst, void *content);
void		malloc_redir(t_token **cmd_tokens, int i);
void		redir_heredoc(t_token *cmd_tokens, t_list *line_lst,
				t_list *env_lst, int i);

/* signal.c */
void		handle_signal(int sig); // signal.c main.c
void		handle_cmd(int sig);
void		handle_signal_heredoc(int sig);

/* mini_utils.c */
int			free_str(char *str);
void		free_char(char **str);
void		free_input(t_input *input);
void		free_tokens(t_token *tokens);
void		free_lst_content(t_list *lst, int sign);
#endif
