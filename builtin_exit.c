#include "minishell.h"
#include "builtin.h"

static long long	my_atoi(const char *str)
{
	long long	result;
	int		sign;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		if (result > 9223372036854775807)
		{
			if (sign > 0)
				return (-1);
			else
				return (1);
		}
		str++;
	}
	return (result * sign);
}

void	my_exit(char** arg, t_list *env)
{
	int i;
	long long status;

	i = 0;
	ft_printf("exit\n");
	if (arg[1] == NULL)
		exit(0);
	while (arg[1] && arg[1][i]) 	//check if arg[1] is numeric
	{
		if (arg[1][i] == '+' || arg[1][i] == '-')
			i++;
		if (ft_isdigit(arg[1][i]) == 0)
		{
			ft_putstr_fd(" numeric argument required\n", 2);
			g_exitcode = 255;
			exit(g_exitcode);
		}
		i++;
	}
	status = my_atoi(arg[1]);
	if (status > 9223372036854775807)
		ft_putstr_fd(" numeric argument required\n", 2);
	status = (unsigned char)my_atoi(arg[1]);
	g_exitcode = status;
	if (arg[2])
	{
		g_exitcode = 1;
		ft_putstr_fd(" too many arguments\n", 2);
	}
	exit(g_exitcode);
}

/* create exit function with no option */
/*
** Minimum long value:
** exit -9223372036854775808--> 0
** exit 9223372036854775807 --> 255
** exit -9223372036854775807--> 1
** exit -9223372036854775809 --> 255
	//char* a4 = "9223372036854775808";
	//char* b3 = "-9223372036854775807";
	//char* b4 = "-9223372036854775808";
	//char* b5 = "-9223372036854775809";
	//printf("num=%s, atoi=%d, unsigned=%hhu\n", a4, atoi(a4), (unsigned char)atoi(a4));
	//printf("num=%s, my_atoi=%llu, unsigned=%hhu\n", a4, my_atoi(a4), (unsigned char)my_atoi(a4));
	//printf("num=%s, ft_atoi=%lld, unsigned=%hhu\n", b3, my_atoi(b3), (unsigned char)my_atoi(b3));
	//printf("num=%s, ft_atoi=%lld, unsigned=%hhu\n", b4, my_atoi(b4), (unsigned char)my_atoi(b4));
	//printf("num=%s, ft_atoi=%lld, unsigned=%hhu\n", b5, my_atoi(b5), (unsigned char)my_atoi(b5));
*/
