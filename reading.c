#include "shell.h"
/**
 * read_line - reads input from standard input
 * @data: Program data
 * Return: returns the line read
 */
ssize_t read_line(shell_info *data)
{
	char line[BUF_SIZE] = {'\0'}, *trimmed;
	ssize_t bytes_read;
	static char *commands[MAX_TOKENS] = {NULL};
	int i = 0;

	if (commands[0] == NULL)
	{
		bytes_read = read(data->fd, line, BUF_SIZE);

		/* Check for EOF */
		if (bytes_read == 0)
		{
			free_all_data(data), exit(errno);
		}

		/* Split input into lines of command if needed */
		commands[i] = _strdup(_strtok(line, "\n"));
		while (commands[i])
			commands[++i] = _strdup(_strtok(NULL, "\n"));
	}

	if (commands[0])
	{
		trimmed = _strtrim(commands[0]);
		if (_strncmp("alias ", commands[0], 6) == 0)
			data->cmdline = expand_variables(trimmed, data);
		else
			data->cmdline = expand_variables(expand_alias(trimmed, 1, data), data);
	}
	else
	{
		data->cmdline = commands[0];
	}
	/**
	 * Shift the commands array so the first index
	 * can point to the next command.
	 */
	for (i = 0; commands[i]; i++)
		commands[i] = commands[i + 1];
	return (data->cmdline ? _strlen(data->cmdline) : 0);
}
