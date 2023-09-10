#include <stdio.h>
#include <string.h>

// Global variable environ that holds environment variables
extern char **environ;

char *_getenv(const char *name)
{
	// Iterate through the environment variables
	for (char **env = environ; *env != NULL; env++)
	{
		// Find the '=' character in the current environment variable
		char *equal_sign = strchr(*env, '=');

		if (equal_sign != NULL)
		{
			// Calculate the length of the variable name
			size_t name_length = equal_sign - *env;

			// Check if the current variable matches the desired name
			if (strncmp(*env, name, name_length) == 0 && name[name_length] == '\0')
			{
				// Return a pointer to the value part of the environment variable
				return equal_sign + 1;
			}
		}
	}

	// Environment variable not found
	return NULL;
}

void print_path_directories()
{
	// Get the value of the PATH environment variable
	char *path = _getenv("PATH");

	if (path == NULL)
	{
		printf("PATH environment variable not found.\n");
		return;
	}

	// Tokenize the PATH variable using ':' as the delimiter
	char *token = strtok(path, ":");

	printf("Directories in PATH:\n");

	// Iterate through and print each directory
	while (token != NULL)
	{
		printf("%s\n", token);
		token = strtok(NULL, ":");
	}
}

int main()
{
	// Example usage of _getenv
	const char *var_name = "PATH";
	char *var_value = _getenv(var_name);

	if (var_value != NULL)
	{
		printf("%s=%s\n", var_name, var_value);
	}
	else
	{
		printf("Environment variable %s not found.\n", var_name);
	}

	// Call the function to print PATH directories
    print_path_directories();

	return 0;
}
