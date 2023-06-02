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
		if (arg[i] == '-' && is_equal_sign(arg, i) == 0)
			return (printf_error(" not a valid identifier\n", 1));
		i++;
	}
	i = 0;
	while ((arg[i]))
	{
		if (arg[i] == '=')
			return (printf_error(" not a valid identifier\n", 1));
		else
			i++;
	}
	g_exitcode = 0;
	return (0);
}

static void	remove_argument(t_list **env, t_list *current, t_list *previous)
{
	char	**env_content;

	env_content = (char **)current->content;
	if (previous == NULL)
		*env = (*env)->next;
	else
		previous->next = current->next;
	free(env_content[0]);
	free(env_content[1]);
	free(current);
}

static int	find_argument(char *arg, t_list **current, t_list **previous,
		int *is_found)
{
	char	**env_content;

	env_content = (char **)(*current)->content;
	if (ft_strncmp(arg, env_content[0], ft_strlen(arg)) == 0)
	{
		*is_found = 1;
		return (1);
	}
	else
	{
		*previous = *current;
		*current = (*current)->next;
		g_exitcode = 0;
		return (0);
	}
}

void	my_unset(char **arg, t_list **env)
{
	int		i;
	int		is_found;
	t_list	*current;
	t_list	*previous;

	i = 1;
	while (arg[i])
	{
		is_found = 0;
		current = *env;
		previous = NULL;
		while (current)
		{
			if (is_valid_argument(arg[i]) == 1)
				break ;
			if (find_argument(arg[i], &current, &previous, &is_found) == 1)
				break ;
		}
		if (current && is_found == 1)
			remove_argument(env, current, previous);
		i++;
	}
	if (!arg[0])
		g_exitcode = 0;
}
 */


static int	isinvalid(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			perror(" not a valid identifier\n");
			g_exitcode = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

void	my_unset(char **args, t_list **env)
{
	int		i;
	t_list	*pre;
	t_list	*tmp;

	i = 1;
	pre = NULL;
	while (args[i])
	{
		tmp = *env;
		if (isinvalid(args[i]))
			return ;
		while (tmp)
		{
			if (!ft_strncmp(((char **)tmp->content)[0], args[i],
					ft_strlen(args[i]) + 1))
				break ;
			pre = tmp;
			tmp = tmp->next;
		}
		if (tmp)
		{
			if (!pre)
				(*env) = (*env)->next;
			else
				pre->next = tmp->next;
			free_char((char **)tmp->content);
			free(tmp);
			tmp = NULL;
		}
		i++;
	}
}
