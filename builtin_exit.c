#include "builtin.h"

/* why the first if does not exit? */
static void	handle_error(char *str)
{
	int	i;

	if (str[0] == '-')
	{
		if ((ft_strlen(str) > 20) || (ft_strlen(str) == 20
			&& ft_strncmp(str, "-9223372036854775808", 20) > 0))
			ft_error("minishell: exit: numeric argument required", 255, 0);
	}
	else if ((ft_strlen(str) > 19) || (ft_strlen(str) == 19 && ft_strncmp(str,
				"9223372036854775807", 19) > 0))
		ft_error("minishell: exit: numeric argument required", 255, 0);
	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			ft_error("minishell: exit: numeric argument required", 255, 0);
		i++;
	}
}

void my_exit(char** args, int num_args, int cmd_id)
{
	long long ret;
	int i;
	int sign;

	i = -1;
	sign = 1;
	ret = 0;
	if (cmd_id == 0)
		printf("exit\n");
	if (args[1] == NULL)
		exit(0);
	handle_error(args[1]);
	if (num_args > 2)
	{
		ft_error("minishell: exit: too many arguments", 1, 1);
		g_exitcode = 1;
		return ;
	}
	if ((args[1][0] == '-' && (sign = -1)) || args[1][0] == '+')
		i++;
	while (args[1][++i])
	{
		if (args[1][i] >= '0' && args[1][i] <= '9')
			ret = ret * 10 + (args[1][i] - '0');
	}
	exit((unsigned char)ret * sign);
}

