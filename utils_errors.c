#include "shell.h"

/**
 * _print_err - Prints to the std error
 * @err: What to print
 * Return: Number of characters printed
 */
ssize_t _print_err(char *err)
{
	return (write(STDERR_FILENO, err, _strlen(err)));
}

/**
 * print_error_header - Prints the error header
 * @data: Program data
 * Return: void
 */
void print_error_header(shell_info *data)
{
	char exec_count[10] = {'\0'};

	number_to_string(exec_count, data->execution_count);
	_print_err(data->name);
	_print_err(": ");
	_print_err(exec_count);
	_print_err(": ");
	_print_err(data->args[0]);
	_print_err(": ");
}

/**
 * print_error - Handles error printing
 * @data: Program data
 * Return: Void
 */
void print_error(shell_info *data)
{
	if (_strcmp(data->args[0], BUILTIN_ALIAS))
		print_error_header(data);
	if (errno == 126 || errno == 127)
		_print_err(errno == 127 ? "not found\n" : "Permission denied\n");

	if (_strcmp(data->args[0], BUILTIN_CD) == 0)
	{
		_print_err("can't cd to ");
		_print_err(data->args[1]);
		_print_err("\n");
	}

	if (_strcmp(data->args[0], BUILTIN_EXIT) == 0)
	{
		_print_err("Illegal number: ");
		_print_err(data->args[1]);
		_print_err("\n");
	}
}
