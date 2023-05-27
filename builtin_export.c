#include "builtin.h"

static int	is_valid_argument(char *arg, t_list *env)
{
	int	i;
	int	ret;

	i = 0;
	if (ft_isalpha(arg[0]) == 0 && arg[0] != '_')
		return (printf_error(" inot a valid identifier", 1));
	while (arg[i])
	{
		if (arg[i] == '-' && is_equal_sign(arg, i) == 0)
			return (printf_error(" inot a valid identifier", 1));
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
	t_list	*node;
	char	**env_content;
	int		len;

	len = 0;
	env_content = env_split(arg, '=');
	if (env_find_and_replace(env, env_content[0], env_content[1]) == 0)
	{
		node = ft_lstnew(env_content);
		if (!node)
			ft_error("cann't create a new node.\n", 1);
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
	char	**env_content;
	int		is_valid;

	i = 0;
	while (arg[i])
	{
		is_valid = is_valid_argument(arg[i], env);
		if (is_valid == 1)
			break ;
		add_argument(env, arg[i]);
		i++;
		g_exitcode = 0;
	}
	if (!arg[0] && empty_aguments(env) == 0)
		g_exitcode = 0;
}
