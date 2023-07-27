#include "shell.h"

/**
 * print_environment - Handles the `env` built-in command
 * @data: Program data
 * Return: The status of the execution
 */
int print_environment(shell_info *data)
{
	int i = 0;

	(void)data;

	while (environ[i] != NULL)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	errno = 0;
	return (EXIT_SUCCESS);
}

/**
 * builtin_exit - Handles the builtin exit command
 * @data: Program data
 * Return: Nothing
 */
int builtin_exit(shell_info *data)
{
	int status = errno; /*this is the default exit status */

	if (data->args[1] != NULL)
	{
		status = _atoi(data->args[1]);
		if (!_isdigit(data->args[1]) || status < 0)
		{
			errno = 2;
			if (isatty(STDIN_FILENO))
				return (-1);
			print_error(data);
			status = 2;
		}
	}

	free_all_data(data);
	exit(status);
}
/**
 * builtin_setenv - Initialize a new environment variable
 * @data: program data
 * Return: 0 if successful otherwise, -1
 */
int builtin_setenv(shell_info *data)
{
	int temp = _setenv(data->args[1], data->args[2]);

	return (temp);
}
/**
 *  builtin_unsetenv - deletes an existing env variable
 *  @data: Program data
 *  Return: 0 if successful
 */
int builtin_unsetenv(shell_info *data)
{
	int temp = _unsetenv(data->args[1]);

	return (temp);
}

/**
 * builtin_cd - Handles the cd command
 * @data: Program data
 * Return: The status of the execution
 */
int builtin_cd(shell_info *data)
{
	char *dir = data->args[1];
	char pwd[1024], *home;
	int status, is_prev = 0;

	getcwd(pwd, 1024);
	home = _getenv("HOME");

	/* Check if no argument */
	if (dir == NULL)
		dir = home ? home : pwd;

	/* Check if the argument is - */
	if (_strcmp(dir, "-") == 0)
	{
		is_prev = 1;
		/* cd to the OLDPWD if it exist else PWD */
		dir = _getenv("OLDPWD");
		if (!dir)
			dir = pwd;
	}

	status = chdir(dir);
	if (status == EXIT_SUCCESS)
	{
		_setenv("OLDPWD", pwd);
		getcwd(pwd, 1024);
		_setenv("PWD", pwd);
		if (is_prev)
			write(STDOUT_FILENO, pwd, _strlen(pwd)), write(STDOUT_FILENO, "\n", 1);
	}

	return (status);
}
