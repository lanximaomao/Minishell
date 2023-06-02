#include "builtin.h"

/* pwd with no options */
void	my_pwd(void)
{
	char	buf[1024];

	if (getcwd(buf, sizeof(buf)) != NULL)
		ft_printf("%s\n", buf);
	g_exitcode = 0;
}
