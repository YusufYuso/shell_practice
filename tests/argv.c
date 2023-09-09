#include <stdio.h>


int main(__attribute__((unused))int argc, char *argv[])
{
	int i;

	for (i = 1; argv[i] != NULL ; i++)
	{
		printf("%s\n", argv[i]);
	}
    return 0;
}
