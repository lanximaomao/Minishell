#include "builtin.h"

/*
** split function is used here to create a char**
*/
static void	handle_oldpwd(char *buf, t_list *env)
{
	char	*ex_arg;
	char	**arg;

	if (env_find_and_replace(env, "OLDPWD", buf) == 0)
	{
		ex_arg = ft_strjoin("OLDPWD=", buf);
		if (!ex_arg)
			ft_error("Strjoin function fail", MALLOC, 0);
		arg = ft_split(ex_arg, '$');
		if (!arg)
			ft_error("Split function fail", MALLOC, 0);
		my_export(arg, env);
	}
	env_find_and_replace(env, "OLDPWD", buf);
}

void	my_cd(char **arg, t_list *env)
{
	char	buf[1024];
	char	*home;
	int		is_null;

	if (getcwd(buf, sizeof(buf)) != NULL)
		handle_oldpwd(buf, env);
	if (arg[0] == NULL)
	{
		is_null = 1;
		home = env_handler(env, "HOME");
		arg[0] = ft_strdup(home);
	}
	if (chdir(arg[0]) != 0)
	{
		g_exitcode = 1;
		ft_putstr_fd(" No such file or directory\n", 2);
		return ;
	}
	if (getcwd(buf, sizeof(buf)) != NULL)
		env_find_and_replace(env, "PWD", buf);
	if (is_null == 1)
		free(arg[0]);
	g_exitcode = 0;
}
