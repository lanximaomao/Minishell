#include "../minishell.h"

static void handle_error(char *str)
{
	int i;

	if (str[0] == '-')
	{
		if ((ft_strlen(str) > 20) || (ft_strlen(str) == 20 // include '-', -9223372036854775808
			&& ft_strncmp(str, "-9223372036854775808", 20)) > 0)
			perror(" numeric argument required");
	}
	else if ((ft_strlen(str) > 19) || (ft_strlen(str) == 19
			&& ft_strncmp(str, "9223372036854775807", 19) > 0))
	{
		perror(" numeric argument required");
		exit(255);
	}
	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			perror(" numeric argument required");
			exit(255);
		}
		i++;
	}
	return ;
}

void my_exit(char** args)
{
	long long ret;
	int i;
	int sign;

	i = -1;
	sign = 1;
	ret = 0;
	printf("exit\n");
	handle_error(args[1]);
	if (args[2])
	{
		perror(" too many arguments\n");
		exit(1);
	}
	if (args[1] == NULL)
		exit(EXIT_SUCCESS);
	if ((args[1][0] == '-' && (sign = -1)) || args[1][0] == '+')
		i++;
	while (args[1][++i])
	{
		if (args[1][i] >= '0' && args[1][i] <= '9')
			ret = ret * 10 + (args[1][i] - '0');
	}
	exit((unsigned char)ret * sign);
}
