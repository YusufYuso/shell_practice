#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKENS 64

char *read_input()
{
	char *input = NULL;
	size_t len = 0;
	ssize_t read;

	printf("($) ");
	read = getline(&input, &len, stdin);

	if (read == -1)
	{
		if (errno == EINTR)
		{
			// Input interrupted, ignore and continue
			return NULL;
		}
		perror("getline");
		exit(EXIT_FAILURE);
	}

	// Remove trailing newline if present
	if (input[read - 1] == '\n')
	{
		input[read - 1] = '\0';
	}

	return input;
}

char **tokenize_input(char *input)
{
	char **tokens = malloc(MAX_TOKENS * sizeof(char *));
	if (!tokens)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	char *token;
	int token_count = 0;

	token = strtok(input, " ");
	while (token != NULL)
	{
		tokens[token_count] = strdup(token);
		token_count++;
		token = strtok(NULL, " ");
	}

	tokens[token_count] = NULL;

	return tokens;
}

void execute_command(char **tokens) {
    pid_t pid, wpid;
    int status;

    pid = fork();

    if (pid == 0) {
        // Child process
        execvp(tokens[0], tokens);
        fprintf(stderr, "%s: 1: %s: not found\n", tokens[0], tokens[0]);
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Forking error
        perror("fork");
    } else {
        // Parent process
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

int main(void)
{
	char *input;
	char **tokens;

	while (1)
	{
		input = read_input();

		if (input == NULL)
		{
			// Input interrupted, continue
			continue;
		}

		tokens = tokenize_input(input);

		if (tokens[0] != NULL)
		{
			if (strcmp(tokens[0], "exit") == 0)
			{
				// Handle exit command
				free(input);
				free(tokens);
				exit(EXIT_SUCCESS);
			}

			if (strcmp(tokens[0], "cd") == 0)
			{
				// Handle cd command
				if (tokens[1] != NULL)
				{
					if (chdir(tokens[1]) != 0)
					{
						perror("cd");
					}
				}
			}
			else
			{
				execute_command(tokens);
			}
		}

		free(input);
		free(tokens);
	}

	return EXIT_SUCCESS;
}
