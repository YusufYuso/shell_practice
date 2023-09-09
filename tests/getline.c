#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main() {
    char *userInput = NULL;
    size_t len = 0;

    while (1) {
        printf("$ ");

        // Use getline to read user input
        ssize_t bytesRead = getline(&userInput, &len, stdin);

        if (bytesRead == -1) {
            // Handle input error or EOF (Ctrl+D on Linux)
            break;
        }

        // Print the user's input on the next line
        printf("%s", userInput);
    }

    // Free allocated memory
    free(userInput);

    return 0;
}
