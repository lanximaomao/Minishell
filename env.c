#include "builtin.h"
#include "minishell.h"

/*
** this function create a linked list
** and each node contains a enviromental variable's name and value
*/

int	env_init(t_mini *mini, char **env)
{
	int		i;
	char	**env_content;
	t_list	*node;

	i = 0;
	mini->env = NULL;
	while (env[i])
	{
		env_content = ft_split(env[i], '=');
		if (!env_content)
			ft_error("malloc fail or null input?\n", 1);
		node = ft_lstnew(env_content);
		if (!node)
			ft_error("fail to init a node\n", 1);
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

char	*env_handler(t_list *env, char *str)
{
	char	**env_content;
	t_list	*tmp;
	int		len;

	tmp = env;
	env_content = (char **)env->content;
	while (tmp)
	{
		env_content = (char **)tmp->content;
		len = ft_strlen(env_content[0]);
		if (len == ft_strlen(str) && ft_strncmp(str, env_content[0], len) == 0)
			return (env_content[1]);
		tmp = tmp->next;
	}
	return (NULL);
}

/*
** convert enviromental varible from a linked list to a double pointer, char**
** this could be used in execve function call.
*/

char	**env_convert(t_list *env)
{
	int		i;
	char	**ret;
	char	*ret_tmp1;
	t_list	*tmp;
	char	**env_content;

	i = 0;
	tmp = env;
	ret = (char **)malloc(sizeof(char *) * (ft_lstsize(env) + 1)); // to be freed
	if (!ret)
		ft_error("malloc fail.\n", 1);
	ret[ft_lstsize(env)] = NULL;
	while (i < ft_lstsize(env))
	{
		env_content = (char **)tmp->content;
		ret_tmp1 = ft_strjoin(env_content[0], "=");
		if (!ret_tmp1)
			ft_error("malloc fail.\n", 1);
		ret[i] = ft_strjoin(ret_tmp1, env_content[1]); // to be freed
		if (!ret[i])
			ft_error("malloc fail.\n", 1);
		free(ret_tmp1);
		tmp = tmp->next;
		i++;
	}
	return (ret);
}

/* this function is used to update the enviromental varible*/
int	env_find_and_replace(t_list *env, char *to_find, char *to_replace)
{
	char	**env_content;
	t_list	*tmp;
	int		len;

	tmp = env;
	env_content = (char **)env->content;
	while (tmp)
	{
		env_content = (char **)tmp->content;
		len = ft_strlen(env_content[0]);
		if (len == ft_strlen(to_find) && ft_strncmp(to_find, env_content[0],
				len) == 0)
		{
			if (ft_strlen(to_replace) <= ft_strlen(env_content[1]))
				ft_strlcpy(env_content[1], to_replace, ft_strlen(to_replace) + 1);
			else
			{
				env_content[1] = ft_realloc(env_content[1], len + 1,
						ft_strlen(to_replace) + 1);
				ft_strlcpy(env_content[1], to_replace, ft_strlen(to_replace) + 1);
			}
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
