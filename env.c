#include "minishell.h"
#include "buidin.h"
#include "pipe.h"

/*
** this function create a linked list
** and each node contains a enviromental variable's name and value
*/

int env_init(t_mini *mini, char **env)
{
	int i;
	char** env_split;
	t_env *env_content;
	t_list *node;

	i = 0;
	mini->env = NULL;
	while (env[i])
	{
		env_split = ft_split(env[i], '=');
		if (!env_split)
			error("malloc fail or null input?\n", 1);
		env_content = malloc(sizeof(t_env) * 1);
		if (!env_content)
			error("malloc fail.\n", 1);
		env_content->env_name = env_split[0]; //to be freed
		env_content->env_value = env_split[1]; // to be freed
		if (!mini->env)
		{
			mini->env = ft_lstnew(env_content);
			if (!mini->env)
				error("fail to init a node\n", 1);
		}
		else
		{
			node = ft_lstnew(env_content);
			if (!node)
				error("fail to init a node\n", 1);
			ft_lstadd_back(&mini->env, node);
		}
		//ft_printf("%s=%s\n", env_content->env_name, env_content->env_value);
		i++;
	}
	//ft_printf("\nbefore\n");
	//my_env(NULL);
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
	return (1);
}

/*
** by giving the name of the enviromental varible, such as HOME
** it returns a string of its values.
*/

char* env_handler(t_list *env, char* str)
{
	t_env *env_content;
	t_list *tmp;
	int len;

	tmp = env;
	while (tmp)
	{
		env_content = (t_env*)tmp->content;
		len = ft_strlen(env_content->env_name);
		//printf("name=%s len=%d\n", env_content->env_name, len);
		if (len < ft_strlen(str))
			len = ft_strlen(str);
		if (ft_strncmp(str, env_content->env_name, len) == 0)
			return(env_content->env_value);
		tmp = tmp->next;
	}
	return(NULL);
}

/*
** convert enviromental varible from a linked list to a double pointer, char**
** this could be used in execve function call.
*/

char** env_convert(t_list* env)
{
	int i;
	int size;
	char** ret;
	char* ret_tmp1;
	char* ret_tmp2;
	t_list *tmp;
	t_env *env_content;

	i = 0;
	size = 0;
	tmp = env;
	size = ft_lstsize(env);
	ret = (char**)malloc(sizeof(char*) * (size + 1)); // to be freed
	if (!ret)
		error("malloc fail.\n", 1);
	ret[size] = NULL;
	while (i <  size)
	{
		env_content = (t_env *)tmp->content;
		ret_tmp1 = ft_strjoin(env_content->env_name, "=");
		ret_tmp2 = ft_strjoin(env_content->env_value, "\n");
		ret[i] = ft_strjoin(ret_tmp1, ret_tmp2); // to be freed
		//printf("%s", ret[i]);
		free(ret_tmp1);
		free(ret_tmp2);
		tmp = tmp->next;
		i++;
	}
	return(ret);
}
