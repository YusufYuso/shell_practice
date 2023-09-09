#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 100

int main() {
    char input[MAX_INPUT_LENGTH];
    
    while (1) {
        printf("SuperSimpleShell> ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            break; // Exit on Ctrl+D or EOF
        }

        // Remove the newline character from the input
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }

        // Fork a child process
        pid_t child_pid = fork();

        if (child_pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (child_pid == 0) {
            // This is the child process

            // Execute the command with its full path
            if (execve(input, (char *[]) {input, NULL}, NULL) == -1) {
                perror("execve");
                exit(EXIT_FAILURE);
            }

            // Shouldn't reach here unless exec fails
            exit(EXIT_SUCCESS);
        } else {
            // This is the parent process
            int status;
            wait(&status);

            if (WIFEXITED(status)) {
                printf("Child process exited with status %d\n", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                printf("Child process terminated by signal %d\n", WTERMSIG(status));
            }
        }
    }

    return 0;
}
