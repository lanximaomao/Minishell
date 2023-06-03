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
