#include "shell.h"

/**
 * init_data - Initializes the program data
 * @data: Program data
 * Return: void
 */
void init_data(shell_info *data)
{
	ops_data logic_data = {NULL};
	char **env;
	char *var;
	int i;

	env = malloc(64 * sizeof(char *));
	if (!env)
	{
		perror("Allocation error");
		exit(EXIT_FAILURE);
	}
	for (i = 0; environ[i]; i++)
	{
		var = _strdup(environ[i]);
		env[i] = var;
	}
	env[i] = NULL;
	environ = env;

	data->cmd = NULL;
	data->cmdline = NULL;
	data->execution_count = 0;
	data->args = NULL;
	data->cmdlist = NULL;
	data->al = NULL;
	data->logic_data = &logic_data;
}

/**
 * is_builtin - Checks if the current command is builtin
 * @data: Program data
 * Return: The exit code of the builtin command
 * execution process else -1 if not builtin
 */
int is_builtin(shell_info *data)
{
	int i = 0;
	builtin_action actions[] = {
		{BUILTIN_EXIT, builtin_exit},
		{BUILTIN_CD, builtin_cd},
		{BUILTIN_ENV, print_environment},
		{BUILTIN_SETENV, builtin_setenv},
		{BUILTIN_UNSETENV, builtin_unsetenv},
		{BUILTIN_ALIAS, builtin_alias},
		{NULL, NULL}};

	while (actions[i].cmd)
	{
		if (_strcmp(data->args[0], actions[i].cmd) == 0)
			return (actions[i].action(data));
		i++;
	}

	return (NOT_BUILTIN);
}
