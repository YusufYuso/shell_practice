#include <stdio.h>

int main(int argc, char *argv[], char *env[])
{
	// Print the address of the env parameter
	printf("Address of env (parameter): %p\n", (void *)env);

	// Print the address of the environ global variable
	extern char **environ;
	printf("Address of environ (global variable): %p\n", (void *)environ);

	// Check if env and environ are the same
	if (env == environ)
	{
		printf("env and environ point to the same memory location.\n");
	}
	else
	{
		printf("env and environ do not point to the same memory location.\n");
	}

	return 0;
}
