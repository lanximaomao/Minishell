#include "builtin.h"

void	my_cd(char **arg, t_list *env)
{
	char	buf[1024];
	char	*home;
	int		is_null;

	if (getcwd(buf, sizeof(buf)) != NULL)
		env_find_and_replace(env, "OLDPWD", buf);
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
