#include <stdio.h>

int main(int argc, char** argv)
{
	int i;

	i = 1;
	if (argc == 1)
		return(1);
	while (argv[i])
	{
		printf("[%d] = [%s]\n", i, argv[i]);
		i++;
	}
	return(0);
}

/*

> ./parsing '"'
[1] = ["]
> ./parsing "'"
[1] = [']
> ./parsing  " "''
[1] = [ ]
> ./parsing  " "' '
[1] = [  ]
> ./parsing  " " ' '
[1] = [ ]
[2] = [ ]
> ./parsing  "''"
[1] = ['']
> ./parsing  '""'
[1] = [""]
> ./parsing  " " ' ' ''''
[1] = [ ]
[2] = [ ]
[3] = []
> ./parsing pwd '$HOME""'
[1] = [pwd]
[2] = [$HOME""]

> ./parsing 'p'wd '$HOME""'
[1] = [pwd]
[2] = [$HOME""]

> ./parsing 'p'wd '$HOME""''"'
[1] = [pwd]
[2] = [$HOME"""]

> ./parsing 'p'wd '$HOME" "''"'
[1] = [pwd]
[2] = [$HOME" ""]

> ./parsing 'p'wd '$HOME" "   ''"'
[1] = [pwd]
[2] = [$HOME" "   "]

> ./parsing ' p 'wd '$HOME""''"'
[1] = [ p wd]
[2] = [$HOME"""]

> ./parsing 'p 'w d '$HOME""''"'
[1] = [p w]
[2] = [d]
[3] = [$HOME"""]

> ./parsing 'p 'w d "$H O M E" " "''"''"
[1] = [p w]
[2] = [d]
[3] = [ O M E]
[4] = [ '']
*/

/*
1. seperate by space, but space inside a single and double quote does not count as separator;
2. within double quote, replace args with true variable value;
3. arguments can be null.
*/
