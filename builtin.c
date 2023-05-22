#include "minishell.h"
#include "builtin.h"

/* 	if no cmd is given, just return. this is to avoide the segfault by doing << f1 */
int buildtin_or_not(t_token* token, t_list *env)
{
	int len;

	if (token->cmd == NULL)
		return (0);
	len = ft_strlen(token->cmd);
	if (len == 2 && ft_strncmp(token->cmd, "cd", len) == 0)
		return(1);
	else if (len == 3 && ft_strncmp(token->cmd, "pwd", len) == 0)
		return(2);
	else if (len == 3 && ft_strncmp(token->cmd, "env", len) == 0)
		return(3);
	else if (len == 4 && ft_strncmp(token->cmd, "exit", len) == 0)
		return(4);
	else if (len == 4 && ft_strncmp(token->cmd, "echo", len) == 0)
		return (5);
	else if (len == 5 && ft_strncmp(token->cmd, "unset", len) == 0)
		return (6);
	else if (len == 6 && ft_strncmp(token->cmd, "export", len) == 0)
		return(7);
	return (0);
}

int buildtin_run(t_token* token, t_list *env)
{
	int ret;

	ret = buildtin_or_not(token, env);
	if (ret == 0)
		return (0);
	if (ret == 1)
		my_cd(token->args, env);
	if (ret == 2)
		my_pwd(env);
	if (ret == 3)
		my_env(token->args, env);
	if (ret == 4)
		my_echo(token->args, env);
	if (ret == 5)
		my_echo(token->args, env);
	if (ret == 6)
		my_unset(token->args, env);
	if (ret == 7)
		my_export(token->args, env);
	return(1);
}


void	my_cd(char **arg, t_list *env)
{
	char	buf[1024];
	char *home;
	int is_null;

	if (getcwd(buf, sizeof(buf)) != NULL)
		env_find_and_replace(env, "OLDPWD", buf);
	if (arg[1] == NULL)
	{
		is_null = 1;
		home = env_handler(env, "HOME");
		arg[1] = ft_strdup(home);//to be freed
	}
	if (chdir(arg[1]) != 0)
	{
		g_exitcode = 1;
		ft_putstr_fd(" No such file or directory\n", 2);
		return;
	}
	if (getcwd(buf, sizeof(buf)) != NULL)
		env_find_and_replace(env, "PWD", buf);
	if(is_null == 1)
		free(arg[1]);
	g_exitcode = 0;
}

/*
** pwd with no options
** if there are any argments,just ignore
*/
void	my_pwd(t_list *env)
{
	char	buf[1024];

	if (getcwd(buf, sizeof(buf)) != NULL)
		ft_printf("%s\n", buf);
	g_exitcode = 0;
}

/*
** env with no options or aguments
*/

int	my_env(char **arg, t_list *env)
{
	t_list	*tmp;
	char**	env_content;

	if (arg[1] != NULL)
	{
		g_exitcode = 127;
		ft_printf("env: %s: No such file or directory\n", arg[1]);
		return(g_exitcode);
	}
	tmp = env;
	while (tmp)
	{
		env_content = (char**)tmp->content;
		if (env_content[1][0] != '\0')
			ft_printf("%s=%s\n", env_content[0], env_content[1]);
		tmp = tmp->next;
	}
	g_exitcode = 0;
	return(0);
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

long long	my_atoi(const char *str)
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


/*
export TEST --> no change
export TEST --> TEST=
export TEST=WHATEVER --> TEST=WHATEVER
export TEST=YES,MINIHELL --> TEST=YES,MINIHELL
export TEST=YES MINIHELL --> TEST=YES
*/

/*
** create export function with no optios
** update or create?
*/

void	my_export(char **arg, t_list *env)
{
	int i;
	int j;
	int len;
	char** env_content;

	i = 1;
	len = 0;
	if (!arg[i])
	{
		my_export_no_aguments(env);
		return;
	}
	while (arg[i])
	{
		j = 0;
		if (is_valid_argument(arg[i], env) == 1)
			return;
		while (arg[i][j])
		{
			len = 0;
			if (arg[i][j] != '=')
			{
				while (arg[i][j] && arg[i][j] != '=' && ++len)
					j++;
				env_content = malloc(sizeof(char*) * 3);
				if (!env_content)
					ft_error("malloc fail.\n", 1);
				env_content[0]=ft_substr(arg[i], j-len, len);
				env_content[1]=ft_substr(arg[i], len+1, ft_strlen(arg[i]));
				if (env_content[1] == NULL)
				{
					free(env_content[0]);
					free(env_content[1]);
					free(env_content);
					break;
				}
				env_content[2] = NULL;
				my_export_arguments(env, env_content);
				break;
			}
			else
				j++;
		}
		i++;
	}
	g_exitcode = 0;
	//loop throught the env, 0 means not found
}

//first character should be a ltter or _
//- is not allowed anywhere
// no space before or after equal sign?
int is_valid_argument(char* arg, t_list *env)
{
	int i;
	int ret;

	if (ft_isalpha(arg[0]) == 0 && arg[0] != '_')
	{
		ft_putstr_fd(" not a valid identifier\n", 2);
		g_exitcode = 1;
		return(1);
	}
	while (arg[i])
	{
		if (arg[i] == '-' && is_equal_sign(arg, i) == 0)
		{
			ft_putstr_fd(" not a valid identifier\n", 2);
			g_exitcode = 1;
			return(1);
		}
		i++;
	}
	i = 0;
	while ((arg[i]))
	{
		if(arg[i] == '=')
			return (0);
		else
			i++;
	}
	g_exitcode = 0;
	return(0);
}

int is_equal_sign(char* arg, int i)
{
	while (arg[i])
	{
		if (arg[i] == '=')
			return(1);
		else
			i--;
	}
	return(0);
}

void my_export_arguments(t_list *env, char** env_content)
{
	t_list	*node;

	if (env_find_and_replace(env, env_content[0], env_content[1]) == 0)
	{
		node = ft_lstnew(env_content);
		if (!node)
			ft_error("cann't create a new node.\n", 1);
		ft_lstadd_back(&env, node);
	}
}

// sorting?
void my_export_no_aguments(t_list *env)
{
	t_list *tmp;
	char **env_content;

	tmp = env;
	while (tmp)
	{
		env_content = (char**)tmp->content;
		ft_printf("declare -x %s=\"%s\"\n", env_content[0], env_content[1]);
		tmp = tmp->next;
	}
}

void	my_unset(char **arg, t_list *env)
{
	int i;
	t_list	*current;
	t_list	*previous;
	char** env_content;

	i = 0;
	if (arg[1] == NULL)
		return;
	while (arg[i])
	{
		current = env;
		previous = NULL;
		while (current)
		{
			env_content = (char**)current->content;
			if (ft_strncmp(arg[1], env_content[0], ft_strlen(arg[1])) == 0)
			env_content = (char**)current->content;
			if (ft_strncmp(arg[1], env_content[0], ft_strlen(arg[1])) == 0)
			{
				if (current == NULL) //node not found, just return (return);
					return;
				if (previous == NULL) //remove the head node
					env = current->next;
				else
					previous->next = current->next;
				free(env_content[0]);
				free(env_content[1]);
				free(current);
				break ;
			}
			previous = current;
			current = current->next;
		}

		i++;
	}
	g_exitcode = 0;
	//return(0);
}

/*
** create echo with option -n
*/
void my_echo(char **arg, t_list *env)
{
	int i;
	int nl;

	nl = 0;
	if (!arg[1])
	{
		ft_printf("\n");
		return;
	}
	if (check_n(arg) == 0 && ++nl)
		i = 1;
	else
		i = 2;
	while (arg[i])
	{
		ft_printf("%s", arg[i]);
		if (arg[i+1])
			ft_printf(" ");
		i++;
	}
	if (nl == 1)
		ft_printf("\n");
	g_exitcode = 0;
}

int check_n(char** arg)
{
	int i;

	i = 2;
	if (arg[1][0] && arg[1][0] == '-' && arg[1][1] && arg[1][1] == 'n')
	{
		while (arg[1][i] != '\0')
		{
			if (arg[1][i] == ' ')
				break;
			if (arg[1][i] != 'n')
				return(0);//does not satify -n condition
			i++;
		}
		return(i+1); // satify -n condition
	}
	return(0);
}
