#include "builtin.h"

/* env with no options or aguments */
int	my_env(t_list *env)
{
	t_list	*tmp;
	char	**env_content;

	tmp = env;
	while (tmp)
	{
		env_content = (char **)tmp->content;
		printf("%s=%s\n", env_content[0], env_content[1]);
		// ft_printf("%s=%s\n", env_content[0], env_content[1]);
		tmp = tmp->next;
	}
	g_exitcode = 0;
	return (0);
}
