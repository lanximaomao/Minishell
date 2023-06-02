#include "builtin.h"
#include "minishell.h"

// char	**env_split(char const *s, char c)
// {
// 	char	**str_arr;
// 	size_t	len;

// 	if (!s)
// 		return (NULL);
// 	str_arr = (char **)malloc(sizeof(char *) * (2 + 1));
// 	if (!str_arr)
// 		return (NULL);
// 	while (*s)
// 	{
// 		if (*s != c)
// 		{
// 			len = 0;
// 			while (*s && *s != c && ++len)
// 				s++;
// 			str_arr[0] = ft_substr(s - len, 0, len);
// 			str_arr[1] = ft_substr(s - len, len + 1, ft_strlen(s));
// 			break ;
// 		}
// 		else
// 			s++;
// 	}
// 	str_arr[2] = 0;
// 	return (str_arr);
// }

/*
** this function create a linked list
** and each node contains a enviromental variable's name and value
*/
// void	env_init(t_mini *mini, char **env)
// {
// 	int		i;
// 	int		is_oldpwd;
// 	char	**env_content;
// 	t_list	*node;

// 	i = 0;
// 	mini->env = NULL;
// 	while (env[i])
// 	{
// 		env_content = env_split(env[i], '=');
// 		if (!env_content)
// 			ft_error("malloc fail or null input?\n", 1, 0);
// 		is_oldpwd = ft_strncmp(env_content[0], "OLDPWD", 6);
// 		if (is_oldpwd != 0)
// 		{
// 			node = ft_lstnew(env_content);
// 			if (!node)
// 				ft_error("fail to init a node\n", 1, 0);
// 			ft_lstadd_back(&mini->env, node);
// 		}
// 		else
// 			free_char(env_content);
// 		i++;
// 	}
// }

void	env_init(t_mini *mini, char **env)
{
	int		i;
	char	**env_content;
	t_list	*node;
	char	**old_pwd;

	i = 0;
	mini->env = NULL;
	while (env[i])
	{
		env_content = ft_split(env[i], '=');
		if (!env_content)
			ft_error("Malloc failed", MALLOC, 0);
		node = ft_lstnew(env_content);
		if (!node)
			ft_error("Malloc failed", MALLOC, 0);
		ft_lstadd_back(&mini->env, node);
		i++;
	}
	old_pwd = ft_split("unset OLDPWD", ' ');
	my_unset(old_pwd, &mini->env);
	free_char(old_pwd);
	return ;
}

/*
** by giving the name of the enviromental varible, such as HOME
** it returns a string of its values.
*/
char	*env_handler(t_list *env, char *str)
{
	char	**env_content;
	t_list	*tmp;
	size_t		len;

	tmp = env;
	env_content = (char **)env->content;
	while (tmp)
	{
		env_content = (char **)tmp->content;
		len = ft_strlen(env_content[0]);
		if (len == ft_strlen(str) && ft_strncmp(str, env_content[0], (int)len) == 0)
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
	t_list	*tmp;
	char	**ret;
	char	*ret_tmp;
	char	**env_content;

	i = -1;
	tmp = env;
	ret = (char **)malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	if (!ret)
		ft_error("malloc fail.\n", 1, 0);
	ret[ft_lstsize(env)] = NULL;
	while (++i < ft_lstsize(env))
	{
		env_content = (char **)tmp->content;
		ret_tmp = ft_strjoin(env_content[0], "=");
		if (!ret_tmp)
			ft_error("malloc fail.\n", 1, 0);
		ret[i] = ft_strjoin(ret_tmp, env_content[1]);
		if (!ret[i])
			ft_error("malloc fail.\n", 1, 0);
		free(ret_tmp);
		tmp = tmp->next;
	}
	return (ret);
}

/*
** this function is used to update the enviromental varible
*/
int	env_find_and_replace(t_list *env, char *to_find, char *to_replace)
{
	char	**env_content;
	t_list	*tmp;
	size_t		len;

	tmp = env;
	env_content = (char **)env->content;
	while (tmp)
	{
		env_content = (char **)tmp->content;
		len = ft_strlen(env_content[0]);
		if (len == ft_strlen(to_find) && ft_strncmp(to_find, env_content[0],
				(int)len) == 0)
		{
			if (ft_strlen(to_replace) > ft_strlen(env_content[1]))
				env_content[1] = ft_realloc(env_content[1], len + 1,
						ft_strlen(to_replace) + 1);
			ft_strlcpy(env_content[1], to_replace, ft_strlen(to_replace) + 1);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
