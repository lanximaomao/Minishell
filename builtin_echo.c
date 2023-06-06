#include "builtin.h"

/*
** return -1 means does not satisfy -n condition
*/

static int	check_n(char *arg)
{
	int	i;

	i = 2;
	if (arg[0] && arg[1] && arg[0] == '-' && arg[1] == 'n')
	{
		while (arg[i] != '\0')
		{
			if (arg[i] == ' ')
				break ;
			if (arg[i] != 'n')
				return (-1);
			i++;
		}
		return (1);
	}
	return (-1);
}

void	my_echo(char **arg)
{
	int	i;
	int	nl;

	i = 1;
	nl = 0;
	while (arg[i])
	{
		if (check_n(arg[i]) == -1)
			break ;
		else
			++nl;
		i++;
	}
	while (arg[i])
	{
		ft_printf("%s", arg[i]);
		if (arg[i + 1])
			ft_printf(" ");
		i++;
	}
	if (nl == 0)
		ft_printf("\n");
	g_exitcode = 0;
}
