#include "shell.h"

/**
 * tokenize_input - Splits a string into tokens
 * @data: Program data
 * Return: An array of string tokens
 */
void tokenize_input(shell_info *data)
{
	/* allocates memory for array of strings */
	char **tokens = malloc(MAX_TOKENS * sizeof(char *));
	char *token;
	int count = 0, bufsize = MAX_TOKENS;

	if (!tokens) /*if dynamic allocation was unsuccessful */
	{
		perror("Allocation error");
		exit(EXIT_FAILURE);
	}
	token = _strdup(_strtok(data->cmd, DELIM)); /*splits line into strings */

	while (token != NULL)
	{
		tokens[count] = token;
		count++;
		if (count >= bufsize)
		{
			bufsize += MAX_TOKENS;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				perror("Reallocation error");
				exit(EXIT_FAILURE);
			}
		}
		token = _strdup(_strtok(NULL, DELIM));
	}
	tokens[count] = NULL;
	data->args = tokens;
}
