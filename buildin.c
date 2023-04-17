/*
cd, pwd, env, export, unset, exit
cd and export need to redo
*/

#include "minishell.h"
#include "buidin.h"
#include "env.h"

int is_buildin(char** cmd_args, t_list *env)
{
	int len;

	len = ft_strlen(cmd_args[0]);
	if (len == 2 && ft_strncmp(cmd_args[0], "cd", len) == 0)
	{
		my_cd(cmd_args, env);
		return(1);
	}
	else if (len == 3 && ft_strncmp(cmd_args[0], "pwd", len) == 0)
	{
		my_pwd(env);
		return(1);
	}
	else if (len == 4 && ft_strncmp(cmd_args[0], "exit", len) == 0)
	{
		my_exit(1);
		return(1);
	}
	else if (len == 4 && ft_strncmp(cmd_args[0], "echo", len) == 0)
	{
		printf("\n-----calling my echo buildin:\n");
		my_echo(cmd_args, env);
		return (1);
	}
	else if (len == 5 && ft_strncmp(cmd_args[0], "unset", len) == 0)
	{
		my_unset(cmd_args, env);
		return (1);
	}
	else if (len == 6 && ft_strncmp(cmd_args[0], "export", len) == 0)
	{
		my_export(cmd_args, env);
		return(1);
	}
	return (0);
}

int	my_cd(char **arg, t_list *env)
{
	char	buf[1024];

	//save current directory into OLDPWD

	if (chdir(arg[1]) != 0)
		error("chdir error", 1);
	if (getcwd(buf, sizeof(buf)) != NULL)
	{
		env_find_and_replace(env, "PWD", buf);
	}
	return (1);
}

int	my_pwd(t_list *env)
{
	char	buf[1024];

	if (getcwd(buf, sizeof(buf)) != NULL)
	{
		printf("%s\n", buf);
		return (1);
	}
	return (0);
}

void	my_env(t_list *env)
{
	t_list	*tmp;
	char**	env_content;

	tmp = env;
	while (tmp)
	{
		env_content = (char**)tmp->content;
		ft_printf("%s=%s\n", env_content[0], env_content[1]);
		tmp = tmp->next;
	}
}

/* update or create? */
void	my_export(char **arg, t_list *env)
{
	int i;
	t_env	*env_content;
	t_list	*node;

	//loop throught the string

	node = ft_lstnew(env_content);
	if (!node)
		error("cann't create a new node.\n", 1);
	ft_lstadd_back(&env, node);
}

void	my_unset(char **arg, t_list *env)
{
	t_list	*current;
	t_list	*previous;
	t_env	*env_content;

	current = env;
	previous = NULL;
	while (current)
	{
		env_content = (t_env *)current->content;
		if (ft_strncmp(arg[1], env_content->env_name, ft_strlen(arg[1])) == 0)
			break ;
		previous = current;
		current = current->next;
	}
	if (current == NULL) //node not found, just return (return);
		return;
	if (previous == NULL) //remove the head node
		env = current->next;
	else
		previous->next = current->next;
	free(env_content->env_name);
	free(env_content->env_value);
	free(current);
}

void	my_exit(int status)
{
	kill(getpid(), SIGTERM);
	exit(status);
}

int my_echo(char **arg, t_list *env)
{
	int i;
	int ret;

	if (arg)
		return (0);
	ret = check_n(arg);
	if (ret == 0)
		printf("%s\n", arg[0]);
	else
	{
		arg[0] = arg[0] + ret;
		printf("%s", arg[0]);
	}
	return(0);
}

int check_n(char** arg)
{
	int i;

	i = 2;
	if (arg[0][0] && arg[0][0] == '-' && arg[0][1] && arg[0][1] == 'n')
	{
		while (arg[0][i] != '\0')
		{
			if (arg[0][i] == ' ')
				break;
			if (arg[0][i] != 'n')
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
//	echo(arg);
//	arg = ft_split("-n -m hello", '*');
//	echo(arg);
//	arg = ft_split("-nnn 123 4 56 abcd", '*');
//	echo(arg);
//	arg = ft_split("-nnn 123 4 56 abcd", '*');
//	echo(arg);
//	arg = ft_split("-nnm123 4 56 abcd", '*');
//	echo(arg);
//	arg = ft_split("-nnnnnnnnnnk-- 123 4 56 abcd", '*');
//	echo(arg);
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
