#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int i;

	for (i = 0; i < 5; i++)
	{
		pid_t child_pid = fork();

		if (child_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}

		if (child_pid == 0)
		{
			// This is the child process
			printf("Child %d executing ls -l /tmp:\n", i + 1);

			char *args[] = {"ls", "-l", "/tmp", NULL};
			execve("/bin/ls", args, NULL);

			// If execve returns, there was an error
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else
		{
			// This is the parent process
			int status;
			wait(&status); // Wait for the child to finish
			printf("Child %d exited with status %d\n", i + 1, status);
		}
	}

	return 0;
}
