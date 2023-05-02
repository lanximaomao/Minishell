#ifndef EXECUTOR_H
# define EXECUTOR_H


int cmd_execution_in_children(t_token* token, int size, t_mini *mini);
int is_builtin_no_run(t_token* token, t_list *env);
int handle_io(t_token* token, int* fd_pipe, int cmd_order, int size);
int handle_file(t_token* token);
void handle_pipe_create(int** fd_pipe, int size);
int handle_pipe_close(int **fd_pipe, int size, int which_pipe);
char* get_path_cmd(char* str, t_list *env);
char **get_path_env(t_list *env);
void close_all(int a, int b);

#endif
