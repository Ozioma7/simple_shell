#include "shell.h"

/**
 * handle_sigint - handles the signal int
 * @signal: The signal code
 * Return: void
 */
void handle_sigint(int signal)
{
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, PROMPT, _strlen(PROMPT));
		fflush(stdout);
	}
}
