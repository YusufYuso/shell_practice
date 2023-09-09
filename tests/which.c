#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define PATH_DELIMITER ":"

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Usage: %s filename ...\n", argv[0]);
		return 1;
	}

	char *path = getenv("PATH");

	if (path == NULL)
	{
		printf("PATH environment variable not found.\n");
		return 1;
	}

	char *token = strtok(path, PATH_DELIMITER);

	while (token != NULL)
	{
		for (int i = 1; i < argc; i++)
		{
			char command[strlen(token) + strlen(argv[i]) + 2]; // +2 for '/' and null terminator
			sprintf(command, "%s/%s", token, argv[i]);

			if (access(command, F_OK | X_OK) == 0)
			{
				printf("%s\n", command);
			}
		}

		token = strtok(NULL, PATH_DELIMITER);
	}

	return 0;
}
