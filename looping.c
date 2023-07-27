#include "shell.h"

/**
 * show_prompt - Shows the prompt
 * @data: Program data
 * Return: void
 */
void show_prompt(shell_info *data)
{
	if (data->mode == INTERACTIVE_MODE)
		write(STDOUT_FILENO, PROMPT, _strlen(PROMPT));
}

/**
 * run_command - Runs a single command
 * @data: Program data
 * Return: void
 */
void run_command(shell_info *data)
{
	int builtin, error_no;
	int i;
	ops_data logic_data;

	expand_logical_ops(data->cmd, &logic_data);

	for (i = 0; logic_data.operands[i]; i++)
	{
		/* Check operation */
		if (i > 0)
		{
			if (logic_data.operators[i - 1] == LOGICAL_AND && errno != 0)
				break;
			if (logic_data.operators[i - 1] == LOGICAL_OR && errno == 0)
				break;
		}

		data->logic_data = &logic_data;
		data->cmd = _strtrim(_strdup(logic_data.operands[i]));
		tokenize_input(data);

		builtin = error_no = is_builtin(data);

		if (builtin == NOT_BUILTIN)
			error_no = exec_command(data);

		if (error_no != EXIT_SUCCESS)
			print_error(data);

		/* Free the data for the current command */
		free_program_data(data);
	}

	/* Free operands */
	free_array_of_pointers(logic_data.operands);
}

/**
 * shell_loop - Main shell
 * @data: Data of the shell
 */
void shell_loop(shell_info *data)
{
	ssize_t cmd_length, i;

	errno = 0; /* Set the initial errno */

	while (++(data->execution_count))
	{
		show_prompt(data);
		cmd_length = read_line(data);

		if (cmd_length == 0)
			continue;

		build_command_list(data);

		for (i = 0; data->cmdlist[i]; ++i)
		{
			data->cmd = data->cmdlist[i];
			if (check_comment(data))
			{
				if (!data->cmd[0])
					errno = 0, free_program_data(data);
				else
					run_command(data);
				break;
			}

			run_command(data);
		}

		/* Free the command list */
		free_array_of_pointers(data->cmdlist);
	}
}
