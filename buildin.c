/*
cd, pwd, env, export, unset, exit
*/

#include "buidin.h"
#include "minishell.h"

int	cd(char **arg)
{
	if (chdir(arg[0]) != 0)
		error("chdir error", 1);
	pwd(NULL);
	return (1);
}

int	pwd(char **arg)
{
	char	buf[1024];

	if (getcwd(buf, sizeof(buf)) != NULL)
	{
		printf("%s\n", buf);
		return (1);
	}
	return (0);
}

void	print_env(char **arg)
{
	t_list	*tmp;
	t_env	*env_content;

	tmp = mini->env;
	while (tmp)
	{
		env_content = (t_env *)tmp->content;
		ft_printf("%s=%s\n", env_content->env_name, env_content->env_value);
		tmp = tmp->next;
	}
}

void	export(char **arg)
{
	char	**arg_split;
	t_env	*env_content;
	t_list	*node;

	arg_split = ft_split(arg[0], '='); // to be freed
	env_content->env_name = arg_split[0];
	env_content->env_value = arg_split[1];
	node = ft_lstnew(env_content);
	if (!node)
		error("cann't create a new node.\n", 1);
	ft_lstadd_back(&mini->env, node);
}

void	unset(char **arg)
{
	t_list	*current;
	t_list	*previous;
	t_env	*env_content;

	current = mini->env;
	previous = NULL;
	while (current)
	{
		env_content = (t_env *)current->content;
		if (ft_strncmp(arg[0], env_content->env_name, ft_strlen(arg[0])) == 0)
			break ;
		previous = current;
		current = current->next;
	}
	if (current == NULL) //node not found, just return (return);
	if (previous == NULL) //remove the head node
		mini->env = current->next;
	else
		previous->next = current->next;
	free(env_content->env_name);
	free(env_content->env_value);
	free(current);
}

void	my_exit(int status)
{
	kill(getpid(), SIGTERM);
	exit(status);
}
