#include "builtin.h"

/* return (0) means does not satisfy -n condition */
static int	check_n(char **arg)
{
	int	i;

	i = 2;
	if (arg[1][0] && arg[1][1] && arg[1][0] == '-' && arg[1][1] == 'n')
	{
		while (arg[1][i] != '\0')
		{
			if (arg[1][i] == ' ')
				break ;
			if (arg[1][i] != 'n')
				return (0);
			i++;
		}
		return (i + 1);
	}
	return (0);
}

void	my_echo(char **arg)
{
	int	i;
	int	nl;

	nl = 0;
	if (!arg[1])
	{
		ft_printf("\n");
		return ;
	}
	if (check_n(arg) == 0 && ++nl)
		i = 1;
	else
		i = 2;
	while (arg[i])
	{
		ft_printf("%s", arg[i]);
		if (arg[i + 1])
			ft_printf(" ");
		i++;
	}
	if (nl == 1)
		ft_printf("\n");
	g_exitcode = 0;
}
