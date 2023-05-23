#include "minishell.h"
#include "builtin.h"

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

void	my_unset(char **arg, t_list *env)
{
	int i;
	t_list	*current;
	t_list	*previous;
	char** env_content;

	i = 0;
	if (arg[1] == NULL)
		return;
	while (arg[++i])
	{
		current = env;
		previous = NULL;
		while (current)
		{
			env_content = (char**)current->content;
			if (ft_strncmp(arg[i], env_content[0], ft_strlen(arg[i])) == 0)
				break;
			previous = current;
			current = current->next;
		}
		if (current == NULL) //node not found, just return;
			return;
		if (previous == NULL) //remove the head node
			env = env->next;
		else
			previous->next = current->next;
		free(env_content[0]);
		free(env_content[1]);
		free(current);
	}
	g_exitcode = 0;
	//my_env(arg, env);
}
