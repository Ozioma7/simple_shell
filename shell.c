#include "shell.h"

/**
 * main - Entry point of the shell.
 * @argc: Number of arguments
 * @argv: Values of the arguments passed.
 * Return: 0 if success.
 */
int main(__attribute((unused)) int argc, __attribute((unused)) char *argv[])
{
	shell_info data = {NULL};

	signal(SIGINT, handle_sigint);

	data.fd = STDIN_FILENO;

	if (isatty(STDIN_FILENO) && argc == 1)
		data.mode = INTERACTIVE_MODE;

	/*checks if arguments were given */
	if (argv[1] && argc > 1)
	{
		data.fd = open(argv[1], O_RDONLY);
		if (data.fd == -1)
		{
			errno = 127;
			_print_err(argv[0]);
			_print_err(": 0: Can't open ");
			_print_err(argv[1]);
			_print_err("\n");
			exit(errno);
		}
	}

	init_data(&data);
	data.name = argv[0];

	shell_loop(&data);

	return (0);
}
