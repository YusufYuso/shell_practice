#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to split a string into words
char **splitString(const char *input, const char *delimiter, int *wordCount)
{
	char *copy = strdup(input); // Create a copy of the input string
	if (copy == NULL)
	{
		*wordCount = 0;
		return NULL;
	}

	// Allocate memory for an initial array of pointers (initially NULL)
	char **words = NULL;
	int capacity = 0;
	*wordCount = 0;

	// Tokenize the copy of the string
	char *token = strtok(copy, delimiter);
	while (token != NULL)
	{
		// Check if the array needs to be resized
		if (*wordCount >= capacity)
		{
			capacity += 10; // Increase capacity in steps of 10
			char **temp = realloc(words, capacity * sizeof(char *));
			if (temp == NULL)
			{
				free(copy);
				free(words);
				*wordCount = 0;
				return NULL; // Memory allocation error
			}
			words = temp;
		}

		// Allocate memory for the word and copy it
		words[*wordCount] = strdup(token);
		(*wordCount)++;

		token = strtok(NULL, delimiter);
	}

	// Free the copy of the string and return the array of words
	free(copy);
	return words;
}

int main()
{
	const char *input = "This is a sample sentence";
	const char *delimiter = " ";
	int wordCount;

	// Split the input string into words
	char **words = splitString(input, delimiter, &wordCount);

	if (words != NULL)
	{
		printf("Words in the string:\n");
		for (int i = 0; i < wordCount; i++)
		{
			printf("%s\n", words[i]);
			free(words[i]); // Free each word
		}
		free(words); // Free the array of words
	}
	else
	{
		printf("Memory allocation error.\n");
	}

	return 0;
}
