#include <stdio.h>
#include <unistd.h>

extern char **environ;

int main()
{
	char **env = environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}

	return 0;
}
