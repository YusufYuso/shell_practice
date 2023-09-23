#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

int main()
{
    char *userInput = NULL;
    size_t len = 0;

    while (1)
    {
        printf("$ ");

        // Use getline to read user input
        ssize_t bytesRead = getline(&userInput, &len, stdin);


        if (bytesRead == EOF)
        {
            free(userInput);
            printf("\n");
            exit(0);
        }

        
        userInput[bytesRead - 1] = '\0';

        if (strcmp(userInput, "exit") == 0)
        {
            // printf("\n");
            free(userInput);
            exit(0);
        }

        // Print the user's input on the next line
        printf("%s\n", userInput);
    }

    // Free allocated memory
    free(userInput);

    return 0;
}
