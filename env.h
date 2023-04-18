#ifndef ENV_H
# define ENV_H

void test_env_functions(t_mini *mini);
int env_find_and_replace(t_list *env, char* to_find, char* to_replace);

#endif
