#include "shell.h"

/**
 * free_aliases - frees memory from alias
 * @var: pointer to head node
 */
void free_aliases(alias_list *var)
{
	alias_list *alias = var;
	alias_list *temp;

	while (alias != NULL)
	{
		temp = alias;
		alias = alias->next;
		free(temp->name);
		free(temp->value);
		free(temp);
	}
}

/**
 * free_array_of_pointers - Frees a double pointer
 * @arr: The memory area to free
 * Return: void
 */
void free_array_of_pointers(char **arr)
{
	int i;

	if (!arr)
		return;

	for (i = 0; arr[i]; i++)
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	free(arr);
}

/**
 * free_program_data - Frees the program data
 * @data: Program data
 * Return: void
 */
void free_program_data(shell_info *data)
{
	if (data->args)
		free_array_of_pointers(data->args);
	if (data->cmdline)
		free(data->cmdline);
	if (data->cmd)
		free(data->cmd);
	data->args = NULL;
	data->cmdline = NULL;
	data->cmd = NULL;
}

/**
 * free_all_data - Frees all program data
 * @data: Program data
 * Return: void
 */
void free_all_data(shell_info *data)
{
	if (data->cmdlist && data->mode == INTERACTIVE_MODE)
		free_array_of_pointers(data->cmdlist);

	if (data->fd != STDIN_FILENO)
	{
		if (close(data->fd))
			perror(data->name);
	}

	if (data->logic_data->operands)
		free_array_of_pointers(data->logic_data->operands);

	free_program_data(data);
	free_array_of_pointers(environ);
	free_aliases(data->al);
}
