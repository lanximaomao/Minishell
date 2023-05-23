#include "builtin.h"
#include "minishell.h"

static int	is_equal_sign(char *arg, int i)
{
	while (arg[i])
	{
		if (arg[i] == '=')
			return (1);
		else
			i--;
	}
	return (0);
}

/*
first character should be a letter or _
- is not allowed anywhere
 no space before or after equal sign?first character should be a letter or _
- is not allowed anywhere
 no space before or after equal sign?
 */
static int	is_valid_argument(char *arg, t_list *env)
{
	int	i;
	int	ret;

	if (ft_isalpha(arg[0]) == 0 && arg[0] != '_')
	{
		ft_putstr_fd(" not a valid identifier\n", 2);
		g_exitcode = 1;
		return (1);
	}
	while (arg[i])
	{
		if (arg[i] == '-' && is_equal_sign(arg, i) == 0)
		{
			ft_putstr_fd(" not a valid identifier\n", 2);
			g_exitcode = 1;
			return (1);
		}
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

static int	add_argument(t_list *env, char **arg, int i, int j)
{
	t_list	*node;
	char	**env_content;
	int		len;

	len = 0;
	if (arg[i][j] != '=')
	{
		while (arg[i][j] && arg[i][j] != '=' && ++len)
			j++;
		env_content = malloc(sizeof(char *) * 3);
		if (!env_content)
			ft_error("malloc fail.\n", 1);
		env_content[0] = ft_substr(arg[i], j - len, len);
		env_content[1] = ft_substr(arg[i], len + 1, ft_strlen(arg[i]));
		env_content[2] = 0;
		if (env_find_and_replace(env, env_content[0], env_content[1]) == 0)
		{
			node = ft_lstnew(env_content);
			if (!node)
				ft_error("cann't create a new node.\n", 1);
			ft_lstadd_back(&env, node);
		}
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
	int		j;
	int		len;
	char	**env_content;

	i = 1;
	len = 0;
	if (!arg[i] && empty_aguments(env) == 0)
		return ;
	while (arg[i])
	{
		j = 0;
		while (is_valid_argument(arg[i], env) == 0 && arg[i][j])
		{
			if (add_argument(env, arg, i, j) == 0)
				break ;
			else
				j++;
		}
		i++;
	}
	g_exitcode = 0;
}

/*
export TEST --> no change
export TEST --> TEST=
export TEST=WHATEVER --> TEST=WHATEVER
export TEST=YES,MINIHELL --> TEST=YES,MINIHELL
export TEST=YES MINIHELL --> TEST=YES
*/
