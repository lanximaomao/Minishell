#ifndef EXECUTOR_H
# define EXECUTOR_H

int executor(t_mini *mini);
int cmd_pipe(t_list *cmd_lst, int* fd_pipe, int size, int cmd_order, t_mini *mini);
int handel_file(t_token* token);
void handel_pipe_create(int** fd_pipe, int size);
int handel_pipe_close(int **fd_pipe, int size, int which_pipe);
char* get_path_cmd(char* str, t_list *env);
char **get_path_env(t_list *env);
void close_all(int a, int b);

#endif