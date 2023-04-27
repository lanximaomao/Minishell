#include "minishell.h"
#include "builtin.h"

void test_env_functions(t_mini *mini)
{
	//test env_handler
	//printf("\nenv handler: %s\n", env_handler(mini->env, "HOME"));
	//printf("\nenv handler: %s\n", env_handler(mini->env, "NONE"));
	// test env_converter
	//char** test = env_convert(mini->env);
	//printf("\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", test[0], test[1], test[2], test[3], test[4], test[5], test[6], test[7]);

	//ft_printf("\nbefore\n\n");
	//my_env(mini->env);

	// test env_find_and_replace
	//env_find_and_replace(mini->env, "KEY", "abcde");
	//ft_printf("\n\nafter\n\n");
	//my_env(mini->env);
	//char *str[1024] = {"KEY=12345", NULL};
	//my_export(str);
	//ft_printf("\nafter\n");
	//my_env(NULL);
	//char **str2 = ft_split("KEY=12345", '=');
	//ft_printf("\nafter unset\n");
	//my_unset(str2);
	//my_env(NULL);
	//env_convert(mini->env);
	//printf("%s\n", env_handler(mini->env, "HOME"));
	return;
}
