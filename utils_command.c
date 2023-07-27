#include "shell.h"

/**
 * check_exec - Checks if a file exits and it's an executable
 * @args: Path to the file
 * Return: 1 if all conditions are satisfied.
 */
int check_exec(char *args)
{
	struct stat fileStatus;

	/* If path exists */
	if (stat(args, &fileStatus) == 0)
	{
		/* If path is a directory or is not an executable */
		if (access(args, X_OK) || S_ISDIR(fileStatus.st_mode))
		{
			errno = 126;
			return (COMMAND_ERROR);
		}
		return (1);
	}
	errno = 127;
	return (COMMAND_ERROR);
}

/**
 * build_command_list - Builds the command list for a
 * single command line
 * @data: Program data
 * Return: void
 */
void build_command_list(shell_info *data)
{
	char **commands;
	char *command;
	int i = 0;

	commands = malloc(MAX_TOKENS * sizeof(char *));
	if (!commands)
	{
		perror("Allocation error");
		exit(EXIT_FAILURE);
	}

	while ((command = _strdup(_strtok(i ? NULL : data->cmdline, ";"))))
		commands[i++] = command;
	commands[i] = NULL;
	data->cmdlist = commands;
}

/**
 * check_comment - Checks if a comment exist in a command
 * @data: Program data
 * Return: 1 if comment else 0
 */
int check_comment(shell_info *data)
{
	int i;

	for (i = 0; data->cmd[i]; i++)
	{
		if (data->cmd[i] == '#')
		{
			if (i == 0)
			{
				data->cmd = _strdup("");
				return (1);
			}

			if (data->cmd[i - 1] == ' ')
			{
				data->cmd = _strtok(data->cmd, "#");
				return (1);
			}
		}
	}
	return (0);
}
