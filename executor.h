#ifndef EXECUTOR_H
# define EXECUTOR_H


int cmd_execution_in_children(t_token* token, int size, t_mini *mini);
int buildtin_or_not(t_token* token, t_list *env);
int handle_io(t_token* token, int cmd_order, int size);
int handle_file(t_token* token);

int executor(t_mini *mini, int size);
int single(t_token* token, t_list *env);
char* get_path_cmd(char* str, t_list *env);
char **get_path_env(t_list *env);
void get_exitcode(int size, int* pid, int*status);

#endif
