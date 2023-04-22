#ifndef EXECUTOR_H
# define EXECUTOR_H

int executor(t_mini *mini);
int cmd_single(t_mini *mini);
int cmd_pipe(t_mini *mini, int** fd_pipe, int size, int which_pipe);
int handel_file(t_token* token, int** fd_pipe, int which_pipe, int size);
int handel_file_single(t_token* token);
void handel_pipe_create(int** fd_pipe, int size);
int handel_pipe_close(int **fd_pipe, int size, int which_pipe);
char* get_path_cmd(char* str, t_list *env);
char **get_path_env(t_list *env);

#endif
