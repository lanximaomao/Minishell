#include "minishell.h"
#include "builtin.h"

/* 	if no cmd is given, just return. this is to avoide the segfault by doing << f1 */
int buildtin_or_not(t_token* token, t_list *env)
{
	int len;

	if (token->cmd == NULL)
		return (-1);
	len = ft_strlen(token->cmd);
	if (len == 2 && ft_strncmp(token->cmd, "cd", len) == 0)
		return(1);
	else if (len == 3 && ft_strncmp(token->cmd, "pwd", len) == 0)
		return(2);
	else if (len == 3 && ft_strncmp(token->cmd, "env", len) == 0)
		return(3);
	else if (len == 4 && ft_strncmp(token->cmd, "exit", len) == 0)
		return(4);
	else if (len == 4 && ft_strncmp(token->cmd, "echo", len) == 0)
		return (5);
	else if (len == 5 && ft_strncmp(token->cmd, "unset", len) == 0)
		return (6);
	else if (len == 6 && ft_strncmp(token->cmd, "export", len) == 0)
		return(7);
	return (0);
}

int buildtin_run(t_token* token, t_list **env)
{
	int ret;

	ret = buildtin_or_not(token, *env);
	if (ret == 0)
		return (0);
	if (ret == 1)
		my_cd(token->args, *env);
	if (ret == 2)
		my_pwd(*env);
	if (ret == 3)
		my_env(token->args, *env);
	if (ret == 4)
		my_echo(token->args, *env);
	if (ret == 5)
		my_echo(token->args, *env);
	if (ret == 6)
		my_unset(token->args, env);
	if (ret == 7)
		my_export(token->args, *env);
	return(1);
}


void	my_cd(char **arg, t_list *env)
{
	char	buf[1024];
	char *home;
	int is_null;

	if (getcwd(buf, sizeof(buf)) != NULL)
		env_find_and_replace(env, "OLDPWD", buf);
	if (arg[1] == NULL)
	{
		is_null = 1;
		home = env_handler(env, "HOME");
		arg[1] = ft_strdup(home);//to be freed
	}
	if (chdir(arg[1]) != 0)
	{
		g_exitcode = 1;
		ft_putstr_fd(" No such file or directory\n", 2);
		return;
	}
	if (getcwd(buf, sizeof(buf)) != NULL)
		env_find_and_replace(env, "PWD", buf);
	if(is_null == 1)
		free(arg[1]);
	g_exitcode = 0;
}

/*
** pwd with no options
** if there are any argments,just ignore
*/
void	my_pwd(t_list *env)
{
	char	buf[1024];

	if (getcwd(buf, sizeof(buf)) != NULL)
		ft_printf("%s\n", buf);
	g_exitcode = 0;
}

/*
** env with no options or aguments
*/
int	my_env(char **arg, t_list *env)
{
	t_list	*tmp;
	char**	env_content;

	//printf("head%p\n", env);
	tmp = env;
	while (tmp)
	{
		env_content = (char**)tmp->content;
		//if (env_content)
			ft_printf("%s=%s\n", env_content[0], env_content[1]);
		tmp = tmp->next;
	}
	g_exitcode = 0;
	return(0);
}
