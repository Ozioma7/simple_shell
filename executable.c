#include "shell.h"

/**
 * handle_path - Finds an executable in the system PATH
 * @args: command name
 * Return: Full path of the executable
 */
char *handle_path(char *args)
{
	char *path = _strdup(_getenv("PATH"));
	char *dir = _strtok(path, ":");
	char *cmd_path;
	size_t dir_len, args_len, path_len;

	while (dir != NULL)
	{
		dir_len = _strlen(dir);
		args_len = _strlen(args);
		path_len = dir_len + args_len + 2;

		cmd_path = malloc(path_len);
		if (cmd_path == NULL)
		{
			perror("Memory allocation error");
			exit(EXIT_FAILURE);
		}
		_strcpy(cmd_path, dir);
		_strcat(cmd_path, "/");
		_strcat(cmd_path, args);

		if (access(cmd_path, F_OK) == 0)
		{
			free(path);
			return (cmd_path);
		}
		free(cmd_path);
		dir = _strtok(NULL, ":");
	}
	free(path);
	return (NULL);
}

/**
 * execute - Main external commnand handler
 * @data: Program data
 * Return: Void
 */
void execute(shell_info *data)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0)
	{
		perror(data->name);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(data->args[0], data->args, environ) == -1)
			perror(data->name);
		exit(errno);
	}

	if (pid > 0)
	{
		waitpid(pid, &status, WUNTRACED);
		if (WIFEXITED(status))
			errno = WEXITSTATUS(status);
	}
}

/**
 * exec_command - Handles external commands
 * @data: Program data
 * Return: The error code of the running process
 */
int exec_command(shell_info *data)
{
	char *cmd_path = data->args[0];
	int fileStat;

	if (!(cmd_path[0] == '/' || cmd_path[0] == '.'))
	{
		cmd_path = handle_path(cmd_path);
		if (!cmd_path)
		{
			errno = 127;
			return (COMMAND_ERROR);
		}
		free(data->args[0]);
		data->args[0] = cmd_path;
	}

	fileStat = check_exec(cmd_path);

	/* If the path is a valid path */
	if (fileStat == 1)
	{
		execute(data);
		return (EXIT_SUCCESS);
	}
	return (fileStat);
}
