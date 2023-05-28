#include "builtin.h"

/* why the first if does not exit? */
static void	handle_error(char *str)
{
	int	i;

	if (str[0] == '-')
	{
		if ((ft_strlen(str) > 20) || (ft_strlen(str) == 20 && ft_strncmp(str,
					"-9223372036854775808", 20)) > 0)
			perror(" numeric argument required");
	}
	else if ((ft_strlen(str) > 19) || (ft_strlen(str) == 19 && ft_strncmp(str,
				"9223372036854775807", 19) > 0))
		ft_error(" numeric argument required", 255);
	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			ft_error(" numeric argument required", 255);
		i++;
	}
}

void	my_exit(char **args)
{
	long long	ret;
	int			i;
	int			sign;

	i = 0;
	sign = 1;
	ret = 0;
	ft_printf("exit\n");
	handle_error(args[0]);
	if (args[1])
		ft_error(" too many arguments", 1);
	if (args[0] == NULL)
		exit(0);
	if (args[0][0] == '-')
		sign = -1;
	if (args[0][0] == '-' || args[0][0] == '+')
		i++;
	while (args[0][i])
	{
		if (args[0][i] >= '0' && args[0][i] <= '9')
			ret = ret * 10 + (args[0][i] - '0');
		i++;
	}
	exit((unsigned char)ret * sign);
}
