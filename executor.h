#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/stat.h>

//executor
int		executor(t_mini *mini, int size);
int		loop(t_mini *mini, int size, int *pid);
int		cmd_in_main(int size, t_token *token, t_list *env);
void	get_exitcode(int size, int *pid, int *status);

//child
int		cmd_execution_in_child(t_token *token, t_mini *mini,
			char **env_exe);
void	cmd_with_no_path(t_token *token, t_mini *mini, char **env_exe);
void	cmd_with_full_path(t_token *token, char **env_exe);

//files
int		handle_io(t_token *token, int cmd_order, int size, int *fd_pipe);
int		get_file_fd(t_token *tokens);
int		get_infile_fd(t_token *tokens, int i, int *count_in);
int		get_outfile_fd(t_token *tokens, int i, int *count_out);

//utils
int		create_child(int *pid, int i);
int		contains_slash(const char *str);
void	free_and_close(char **env_exe, int fd_in, int fd_out);
char	*get_path_cmd(char *str, t_list *env);
char	**get_path_env(t_list *env);

#endif
