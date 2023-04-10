#include "minishell.h"
#include "buidin.h"

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

int echo(char **arg)
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
