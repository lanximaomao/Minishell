#include "pipe.h"

void minishell(char *line)
{
	char** str;

	str = ft_split(line, ' ');
	//execve("/bin/ls", str, NULL);
	//execve("/bin/ls", str, update_env());
	execve("/bin/echo", str, update_env());
}

char** update_env()
{
	int size;
	int i;
	char** ret;
	char* ret_tmp1;
	char* ret_tmp2;
	t_list *tmp;
	t_env *env_content;

	i = 0;
	size = 0;
	tmp = mini->env;

	//size
	size = ft_lstsize(mini->env);
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
		free(ret_tmp1);
		free(ret_tmp2);
		//ft_printf("%s + %s = %s\n", env_content->env_name, env_content->env_value, ret[i]);
		tmp = tmp->next;
		i++;
	}
	return(ret);
}


