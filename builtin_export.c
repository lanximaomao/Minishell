#include "builtin.h"
/*
static int	is_valid_argument(char *arg)
{
	int	i;

	i = 0;
	if (ft_isalpha(arg[0]) == 0 && arg[0] != '_')
		return (printf_error(" not a valid identifier\n", 1));
	while (arg[i])
	{
		if (!(ft_isalnum(arg[i]) || ft_isalpha(arg[i]))
			&& is_equal_sign(arg, i) == 0)
			return (printf_error(" not a valid identifier\n", 1));
		i++;
	}
	i = 0;
	while ((arg[i]))
	{
		if (arg[i] == '=')
			return (0);
		else
			i++;
	}
	g_exitcode = 0;
	return (0);
}

static int	add_argument(t_list *env, char *arg)
{
	int		sign;
	t_list	*node;
	char	**env_content;

	sign = 0;
	env_content = env_split(arg, '=');
	while (*arg)
	{
		if (*arg == '=')
			sign = 1;
		arg++;
	}
	if (env_content[1][0] == 0 && sign == 0)
		return (1);
	if (env_find_and_replace(env, env_content[0], env_content[1]) == 0)
	{
		node = ft_lstnew(env_content);
		if (!node)
			ft_error("cann't create a new node", 1, 0);
		ft_lstadd_back(&env, node);
		return (0);
	}
	return (1);
}

static int	empty_aguments(t_list *env)
{
	t_list	*tmp;
	char	**env_content;

	tmp = env;
	while (tmp)
	{
		env_content = (char **)tmp->content;
		ft_printf("declare -x %s=\"%s\"\n", env_content[0], env_content[1]);
		tmp = tmp->next;
	}
	return (0);
}

void	my_export(char **arg, t_list *env)
{
	int		i;
	int		is_valid;

	i = 0;
	while (arg[i])
	{
		is_valid = is_valid_argument(arg[i]);
		if (is_valid == 0)
			add_argument(env, arg[i]);
		if (is_valid == 0)
			g_exitcode = 0;
		else
			g_exitcode = 1;
		i++;
	}
	if (!arg[0] && empty_aguments(env) == 0)
		g_exitcode = 0;
}
 */


static int	isinvalid_env(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '=')
			|| (str[0] == '=') || ft_isdigit(str[0]))
		{
			perror(" not a valid identifier\n");
			g_exitcode = 1;
			return (1);
		}
		if (str[i] == '=')
			break ;
		i++;
	}
	return (0);
}

static char	*ft_muljoin(char **tmp_exp) // len is the length of tmp_exp
{
	int i;
	char *tmp_join;
	char *res;

	i = 1;
	tmp_join = NULL; // for free， strjoin的第一个参数
	res = NULL;
	if (tmp_exp[i] == NULL)
		return (NULL);
	else
		i++;
	res = ft_strdup(tmp_exp[1]);
	while (tmp_exp[i])
	{
		tmp_join = res;
		res = ft_strjoin(tmp_join, "=");
		if (!res)
			ft_error("Malloc failed", MALLOC, 0);
		free_str(tmp_join);
		tmp_join = res;
		res = ft_strjoin(tmp_join, tmp_exp[i]);
		if (!res)
			ft_error("Malloc failed", MALLOC, 0);
		free_str(tmp_join);
		i++;
	}
	return (res);
}

static int	print_export(t_list *env)
{
	int sign;

	sign = 0;
	while (env)
	{
		if (!ft_strncmp(((char **)env->content)[0], "OLDPWD", 6))
			sign = 1;
		printf("declare -x %s=\"%s\"\n", ((char **)env->content)[0], ((char **)env->content)[1]);
		env = env->next;
	}
	if (!sign)
		printf("declare -x OLDPWD\n");
	return (0);
}

static void add_export(t_list **env, char **new_envp)
{
	t_list	*tmp_lst;
	char	**tmp_envp;

	tmp_lst = *env;
	tmp_envp = (char **)tmp_lst->content;
	// 遍历查找这个tmp[0]，有的话替换value
	while (tmp_lst)
	{
		if (ft_strncmp(new_envp[0], tmp_envp[0], ft_strlen(new_envp[0])) == 0)
		{
			free_str(tmp_envp[1]);
			if (new_envp[1])
				tmp_envp[1] = ft_strdup(new_envp[1]);
			else
				tmp_envp[1] = NULL; // 避免”export t1=“的时候segfault
			free_char(new_envp);
			break;
		}
		tmp_lst = tmp_lst->next;
	}
	// 没有的话，添加一个env
	if (tmp_lst == NULL)
		create_lst(env, (char **)new_envp);
}

void	my_export(char **arg, t_list **env)
{
	int		i;
	char	**tmp;
	char	**new_envp;

	i = 1;
	while (arg[i])
	{
		if (isinvalid_env(arg[i]) == 0)
		{
			tmp = ft_split(arg[i], '=');
			if (!tmp)
				return ;
			new_envp = (char **)ft_calloc(sizeof(char *), 3);
			if (!new_envp)
			{
				free_char(tmp);
				return ;
			}
			new_envp[0] = ft_strdup(tmp[0]);
			new_envp[1] = ft_muljoin(tmp);
			free_char(tmp);
			add_export(env, new_envp);
		}
		i++;
	}
	if (!arg[1])
	{
		print_export(*env);
		g_exitcode = 0;
	}
	return ;
}

