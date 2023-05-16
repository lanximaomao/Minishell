#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//int main()
//{
//	char* a1 = "9223372036854775805";
//	char* a2 = "9223372036854775806";
//	char* a3 = "9223372036854775807";
//	char* a4 = "9223372036854775808";
//	char* a5 = "9223372036854775809";

//	char* b1 = "-9223372036854775805";
//	char* b2 = "-9223372036854775806";
//	char* b3 = "-9223372036854775807";
//	char* b4 = "-9223372036854775808";
//	char* b5 = "-9223372036854775809";
//	char* b6 = "-9223372036854775810";
//	char* b7 = "-9223372036854775811";

//	printf("num=%s, atoi=%d, unsigned=%hhu\n", a1, atoi(a1), (unsigned char)atoi(a1));
//	printf("num=%s, atoi=%d, unsigned=%hhu\n", a2, atoi(a2), (unsigned char)atoi(a2));
//	printf("num=%s, atoi=%d, unsigned=%hhu\n", a3, atoi(a3), (unsigned char)atoi(a3));
//	printf("num=%s, atoi=%d, unsigned=%hhu\n", a4, atoi(a4), (unsigned char)atoi(a4));
//	printf("num=%s, atoi=%d, unsigned=%hhu\n", a5, atoi(a5), (unsigned char)atoi(a5));

//	//printf("num=%s, ft_atoi=%d, unsigned=%hhu\n", a1, ft_atoi(a1), (unsigned char)ft_atoi(a1));
//	//printf("num=%s, ft_atoi=%d, unsigned=%hhu\n", a2, ft_atoi(a2), (unsigned char)ft_atoi(a2));
//	//printf("num=%s, ft_atoi=%d, unsigned=%hhu\n", a3, ft_atoi(a3), (unsigned char)ft_atoi(a3));
//	//printf("num=%s, ft_atoi=%d, unsigned=%hhu\n", a4, ft_atoi(a4), (unsigned char)ft_atoi(a4));
//	//printf("num=%s, ft_atoi=%d, unsigned=%hhu\n", a5, ft_atoi(a5), (unsigned char)ft_atoi(a5));

//	printf("\n\nnum=%s, atoi=%d, unsigned=%hhu\n", b1, atoi(b1), (unsigned char)atoi(b1));
//	printf("num=%s, atoi=%d, unsigned=%hhu\n", b2, atoi(b2), (unsigned char)atoi(b2));
//	printf("num=%s, atoi=%d, unsigned=%hhu\n", b3, atoi(b3), (unsigned char)atoi(b3));
//	printf("num=%s, atoi=%d, unsigned=%hhu\n", b4, atoi(b4), (unsigned char)atoi(b4));
//	printf("num=%s, atoi=%d, unsigned=%hhu\n", b5, atoi(b5), (unsigned char)atoi(b5));

//	printf("num=%s, atoi=%d, unsigned=%hhu\n", b6, atoi(b6), (unsigned char)atoi(b6));
//	printf("num=%s, atoi=%d, unsigned=%hhu\n", b7, atoi(b7), (unsigned char)atoi(b7));

//	//printf("num=%s, ft_atoi=%d, unsigned=%hhu\n", b1, ft_atoi(b1), (unsigned char)ft_atoi(b1));
//	//printf("num=%s, ft_atoi=%d, unsigned=%hhu\n", b2, ft_atoi(b2), (unsigned char)ft_atoi(b2));
//	//printf("num=%s, ft_atoi=%d, unsigned=%hhu\n", b3, ft_atoi(b3), (unsigned char)ft_atoi(b3));
//	//printf("num=%s, ft_atoi=%d, unsigned=%hhu\n", b4, ft_atoi(b4), (unsigned char)ft_atoi(b4));
//	//printf("num=%s, ft_atoi=%d, unsigned=%hhu\n", b5, ft_atoi(b5), (unsigned char)ft_atoi(b5));

//	return(0);
//}

int main()
{
	char* str;
	char* str1;

	str = strdup("hello");
	//str1 = strdup(++str);
	str1 = ++str;
	//str1 = --str;
	//printf("%s\n", str1);

	free(str);
	//free(str1);
	return(0);
}
