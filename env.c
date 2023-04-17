#include "minishell.h"
#include "env.h"
#include "buidin.h"
#include "pipe.h"

/*
** this function create a linked list
** and each node contains a enviromental variable's name and value
*/

int env_init(t_mini *mini, char **env)
{
	int i;
	char **env_content;
	t_list *node;

	i = 0;
	mini->env = NULL;
	while (env[i])
	{
		env_content = ft_split(env[i], '=');
		if (!env_content)
			error("malloc fail or null input?\n", 1);
			node = ft_lstnew(env_content);
			if (!node)
				error("fail to init a node\n", 1);
			ft_lstadd_back(&mini->env, node);
		i++;
	}
	//test_env_functions(mini);
	return (1);
}

/*
** by giving the name of the enviromental varible, such as HOME
** it returns a string of its values.
*/

char* env_handler(t_list *env, char* str)
{
	char** env_content;
	t_list *tmp;
	int len;

	tmp = env;
	env_content = (char**)env->content;
	while (tmp)
	{
		env_content = (char**)tmp->content;
		len = ft_strlen(env_content[0]);
		//printf("name=%s len=%d\n", env_content->env_name, len);
		if (len == ft_strlen(str) && ft_strncmp(str, env_content[0], len) == 0)
			return(env_content[1]);
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
	t_list *tmp;
	char** env_content;

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
		env_content = (char**)tmp->content;
		ret_tmp1 = ft_strjoin(env_content[0], "=");
		if (!ret_tmp1)
			error("malloc fail.\n", 1);
		ret[i] = ft_strjoin(ret_tmp1, env_content[1]); // to be freed
		if (!ret[i])
			error("malloc fail.\n", 1);
		//printf("%s", ret[i]);
		free(ret_tmp1);
		tmp = tmp->next;
		i++;
	}
	return(ret);
}

/* this function is used to update the enviromental varible*/
void env_find_and_replace(t_list *env, char* to_find, char* to_replace)
{
	char** env_content;
	t_list *tmp;
	int len;

	tmp = env;
	env_content = (char**)env->content;

	ft_printf("to_find=%s, to_replace=%s\n", to_find, to_replace);

	while (tmp)
	{
		env_content = (char**)tmp->content;

		len = ft_strlen(env_content[0]);
		if (len == ft_strlen(to_find) && ft_strncmp(to_find, env_content[0], len) == 0)
		{
			//ft_printf("now I found:%s\n", env_content[1]);
			free(env_content[1]);
			env_content[1] = ft_strdup(to_replace);
			//ft_printf("after replace:%s\n", env_content[1]);
		}
		tmp = tmp->next;
	}
}
