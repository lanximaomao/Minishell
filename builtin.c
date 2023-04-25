/*
!! update unset
!! update echo
*/

#include "minishell.h"
#include "builtin.h"

int is_buildin(t_token* token, t_list *env)
{
	int len;

	//printf("\n**************** buildin *****************\n");

	//printf("args: %s\n", token->args[0]);
	//printf("args: %s\n", token->args[1]);

	len = ft_strlen(token->cmd);

	if (len == 2 && ft_strncmp(token->cmd, "cd", len) == 0)
	{
		my_cd(token->args, env);
		return(1);
	}
	else if (len == 3 && ft_strncmp(token->cmd, "pwd", len) == 0)
	{
		my_pwd(env);
		return(1);
	}
	else if (len == 4 && ft_strncmp(token->cmd, "exit", len) == 0)
	{
		my_exit(token->args, env);
		return(1);
	}
	else if (len == 4 && ft_strncmp(token->cmd, "echo", len) == 0)
	{
		my_echo(token->args, env);
		return (1);
	}
	else if (len == 5 && ft_strncmp(token->cmd, "unset", len) == 0)
	{
		my_unset(token->args, env);
		return (1);

	}
	else if (len == 6 && ft_strncmp(token->cmd, "export", len) == 0)
	{
		my_export(token->args, env);
		return(1);
	}
	return (0);
}

/*
** cd with only a relative or absolute path
** !!save current directory into OLDPWD
*/

int	my_cd(char **arg, t_list *env)
{
	char	buf[1024];
	char *home;

	home = env_handler(env, "HOME");
	if (arg[1] == NULL)
		arg[1] = ft_strdup(home);//to be freed
	//printf("%s\n", arg[1]);
	if (chdir(arg[1]) != 0)
	{
		ft_printf("No such file or directory.\n");
		return (2);
	}
	if (getcwd(buf, sizeof(buf)) != NULL)
		env_find_and_replace(env, "PWD", buf);
	return (1);
}

/*
** pwd with no options
** if there are any argments,just ignore
*/

int	my_pwd(t_list *env)
{
	char	buf[1024];

	if (getcwd(buf, sizeof(buf)) != NULL)
	{
		ft_printf("%s\n", buf);
		return (1);
	}
	return (0);
}

/*
** env with no options or aguments
*/

void	my_env(t_list *env)
{
	t_list	*tmp;
	char**	env_content;

	printf("calling my env functions.\n");
	tmp = env;
	while (tmp)
	{
		env_content = (char**)tmp->content;
		ft_printf("%s=%s\n", env_content[0], env_content[1]);
		tmp = tmp->next;
	}
}

/* create exit function with no option */

void	my_exit(char** arg, t_list *env)
{
	int i;
	unsigned long long status;

	i = 0;
	ft_printf("exit\n");
	while (arg[1][i]) 	//check if arg[1] is numeric
	{
		if (arg[1][i] == '+' || arg[1][i] == '-')
			i++;
		if (ft_isdigit(arg[1][i]) == 0)
		{
			ft_printf("minishell: exit: %s: numeric argument required.\n", arg[1]);
			exit(255);
			return;
		}
		i++;
	}
	status = ft_atoi(arg[1]);
	if (status > 9223372036854775807)
		ft_printf("minishell: exit: %s: numeric argument required.\n", arg[1]);
	if (arg[2]) // if too many arguments
		ft_printf("minishell: exit: too many arguments.\n");
	status = (unsigned char)ft_atoi(arg[1]);
	exit(status);
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
	t_list	*node;
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
		while (arg[i][j])
		{
			len = 0;
			if (arg[i][j] != '=')
			{
				while (arg[i][j] && arg[i][j] != '=' && ++len)
				{
					j++;
				}
				env_content = malloc(sizeof(char*) * 3);
				if (!env_content)
					ft_error("malloc fail.\n", 1);
				env_content[0]=ft_substr(arg[i], j-len, len);
				env_content[1]=ft_substr(arg[i], len+1, ft_strlen(arg[i]));
				env_content[2] = NULL;
				//ft_printf("env[0]=%s, env[1]=%s, env[3]=%s\n", env_content[0], env_content[1], env_content[2]);
				break;
			}
			else
				j++;
		}
		i++;
	}
	//loop throught the env, 0 means not found
	if (env_find_and_replace(env, env_content[0], env_content[1]) == 0)
	{
		node = ft_lstnew(env_content);
		if (!node)
			ft_error("cann't create a new node.\n", 1);
		ft_lstadd_back(&env, node);
	}
}

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

/* TO BE UPDATED */
void	my_unset(char **arg, t_list *env)
{
	int i;
	t_list	*current;
	t_list	*previous;
	char** env_content;

	i = 0;
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
}

/*
** create echo with option -n
*/

int my_echo(char **arg, t_list *env)
{
	int i;
	int ret;

	//ft_printf("arg[0]=%s, arg[[1]=%s, arg[2]=%s\n", arg[0], arg[1], arg[2]);
	if (!arg[1])
	{
		ft_printf("\n");
		return (0);
	}
	ret = check_n(arg);
	//ft_printf("ret is %d\n", ret);
	if (ret == 0)
	{
		i = 1;
		while (arg[i])
		{
			ft_printf("%s", arg[i]);
			if (arg[i+1])
				ft_printf(" ");
			i++;
		}
		ft_printf("\n");
	}

	else
	{
		i = 2;
		while (arg[i])
		{
			ft_printf("%s", arg[i]);
			if (arg[i+1])
				ft_printf(" ");
			i++;
		}
	}
	return(0);
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

//int main()
//{
//	char **arg;

//	arg = ft_split("", '*');
//	my_echo(arg);
//	my_echo(arg);
//	arg = ft_split("-n -m hello", '*');
//	my_echo(arg);
//	my_echo(arg);
//	arg = ft_split("-nnn 123 4 56 abcd", '*');
//	my_echo(arg);
//	my_echo(arg);
//	arg = ft_split("-nnn 123 4 56 abcd", '*');
//	my_echo(arg);
//	my_echo(arg);
//	arg = ft_split("-nnm123 4 56 abcd", '*');
//	my_echo(arg);
//	my_echo(arg);
//	arg = ft_split("-nnnnnnnnnnk-- 123 4 56 abcd", '*');
//	my_echo(arg);
//	my_echo(arg);
//	return(0);
//}

/*
> echo hello
hello
> echo -n hello
hello>
> echo -nn hello
hello>
> echo -nm hello
-nm hello
> echo -n -m hello
-m hello>
> echo -mn hello
-mn hello
> echo -nnnnnnnnnnnnn hello
hello>
> echo -nnnnnnnnnnnnn hello world
hello world>
> echo -nnnnnnnnnnnnn hello world\n
hello worldn>
> echo hello world\n
hello worldn

> echo -nn -nm hello world
-nm hello world>

echo hello world -nn  yello yorld --> if -n is in the middle, not interpreted
hello world -nn yello yorld

> echo hello he"ll"o0 'he"ll"o1' "he"ll"o2" ""he"ll"o3 he"ll"o4"" ''he"ll"o5 he"ll"o6''
hello hello0 he"ll"o1 hello2 hello3 hello4 hello5 hello6

prog_args=-e
echo $prog_args

echo $HOME = echo "$HOME"
echo '$HOME'
echo "Goodbye, World!" >> hello.txt

echo "-n" --> do nothing
echo '-n' --> do nothing
echo --> newline and return

The echo utility exits 0 on success, and >0 if an error occurs.
*/
