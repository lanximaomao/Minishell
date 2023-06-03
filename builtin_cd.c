#include "builtin.h"

/*
** split function is used here to create a char**
*/
static void	handle_oldpwd(char *buf, t_list **env)
{
	char	*ex_arg;
	char	**arg;

	if (env_find_and_replace(env, "OLDPWD", buf) == 0)
	{
		ex_arg = ft_strjoin("export$OLDPWD=", buf);
		if (!ex_arg)
			ft_error("Strjoin function fail", MALLOC, 0);
		arg = ft_split(ex_arg, '$');
		if (!arg)
			ft_error("Split function fail", MALLOC, 0);
		my_export(arg, env);
		free_str(ex_arg);
		free_char(arg);
	}
	env_find_and_replace(env, "OLDPWD", buf);
}

void	my_cd(char **arg, t_list **env)
{
	char	buf[1024];

	if (getcwd(buf, sizeof(buf)) != NULL)
		handle_oldpwd(buf, env);
	if (arg[1] == NULL)
	{
		if (chdir(env_handler(env, "HOME")) != 0)
		{
			g_exitcode = 1;
			ft_putstr_fd(" No such file or directory\n", 2);
			return ;
		}
	}
	else if (chdir(arg[1]) != 0)
	{
		g_exitcode = 1;
		ft_putstr_fd(" No such file or directory\n", 2);
		return ;
	}
	if (getcwd(buf, sizeof(buf)) != NULL)
		env_find_and_replace(env, "PWD", buf);
	g_exitcode = 0;
}

/*
void	my_cd(char **args, t_list **env)
{
	char *tmp_str;
	char *old_pwd;
	char **oldpwd_envp;
	t_list	*tmp_lst;

	tmp_str = getcwd(NULL, 0);
	old_pwd = ft_strjoin("export OLDPWD=", tmp_str);
	free_str(tmp_str);
	if (!old_pwd)
		ft_error("Malloc failed", MALLOC, 0);
	if (args[1] == NULL)
		chdir(getenv("HOME"));
	else if (chdir(args[1]) == -1)
	{
		g_exitcode = 1;
		ft_error(" No such file or directory\n", FILE_OP, 1);
		return ;
	}
	tmp_lst = *env;
	while (tmp_lst)
	{
		if (!ft_strncmp(((char **)tmp_lst->content)[0], "PWD", 4))
		{
			free_str(((char **)tmp_lst->content)[1]);
			((char **)tmp_lst->content)[1] = ft_strdup(getenv("PWD"));
		}
		tmp_lst = tmp_lst->next;
	}
	oldpwd_envp = ft_split(old_pwd, ' ');
	if (!oldpwd_envp)
		ft_error("Malloc failed", MALLOC, 0);
	free_str(old_pwd);
	my_export(oldpwd_envp, env);
	free_char(oldpwd_envp);
	return ;
}
*/
