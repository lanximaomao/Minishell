#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	char *str;


	str = malloc(1);
	int i = strlen(str);
	return printf("%d", i);
}
