#ifndef EXECUTOR_H
# define EXECUTOR_H

int		executor(t_mini *mini, int size);
void	loop(t_mini *mini, int size, int *pid, int *status);
int		handle_io(t_token *token, int cmd_order, int size, int *fd_pipe);
int		cmd_execution_in_children(t_token *token, int size, t_mini *mini);
void	child_error_handle(t_token *token, t_mini *mini);
int		single_builtin(t_token *token, t_list *env);
char	*get_path_cmd(char *str, t_list *env);
char	**get_path_env(t_list *env);
void	get_exitcode(int size, int *pid, int *status);
int		get_file_fd(t_token *token);
int		get_infile_fd(t_token *token);
int		buildtin_or_not(t_token *token, t_list *env);

#endif
