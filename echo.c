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
*/

int check_n(char** arg);

void echo(char **arg)
{
	//echo "hello world"
	int i;
	int ret;

	i = 0;
	ret = check_n(arg) != 0;
	printf("ret = %d\n", ret);
	while (arg[i])
	{
		printf("%s", arg[i]);
		i++;
	}
	if (ret != 1)
		printf("\n");
}

int check_n(char** arg)
{
	int i;

	i = 2;
	if (arg[0][0] == '-' && arg[0][1] == 'n')
	{
		while (arg[0][i] != '\0')
		{
			//write(1, "here\n", 5);
			if (arg[0][i] != '\0' && arg[0][i] != 'n' && arg[0][1] != ' ')
			{
				printf("char = %c", arg[0][i]);
				write(1, "here\n", 5);
				return(0);
			}
			i++;
		}
		return(1);
	}
	return(0);
}

int main()
{
	char **arg = ft_split("-n hello!", '*');
	echo(arg);
	return(0);
}
