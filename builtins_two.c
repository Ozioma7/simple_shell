#include "shell.h"

/**
 * get_alias - Gets an alias
 * @data: Program data
 * @name: Name of alias to retrieve
 * Return: The alias else NULL
 */
alias_list *get_alias(shell_info *data, char *name)
{
	alias_list *alias = data->al;

	while (alias != NULL)
	{
		if (_strcmp(alias->name, name) == 0)
			return (alias);
		alias = alias->next;
	}

	return (NULL);
}

/**
 * add_alias - creates or modifies alias
 * @name: name of the alias
 * @value: value of the alias
 * @data: Program data
 */
void add_alias(char *name, char *value, shell_info *data)
{
	alias_list *alias = data->al, *prev;
	alias_list *new;

	/* check if the alias already exists */
	while (alias != NULL)
	{
		if (_strcmp(alias->name, name) == 0)
		{
			free(alias->value);
			alias->value = _strdup(value);
			return;
		}
		prev = alias;
		alias = alias->next; /* moves to next node */
	}

	/* if alias doesnt exist, create a new one */
	new = malloc(sizeof(alias_list));
	new->name = _strdup(name);
	new->value = _strdup(value);
	new->next = NULL;
	if (!data->al)
		data->al = new;
	else
		prev->next = new;
}

/**
 * print_alias - prints all or specified aliases
 * @data: Program data
 * @name: alias name
 */
void print_alias(shell_info *data, char *name)
{
	alias_list *alias = data->al;

	while (alias != NULL)
	{
		if (name == NULL) /*print all aliases */
		{
			write(STDOUT_FILENO, alias->name, _strlen(alias->name));
			write(STDOUT_FILENO, "='", 2);
			write(STDOUT_FILENO, alias->value, _strlen(alias->value));
			write(STDOUT_FILENO, "'\n", 2);
		}
		else
		{
			if (_strcmp(alias->name, name) == 0)
			{
				write(STDOUT_FILENO, alias->name, _strlen(alias->name));
				write(STDOUT_FILENO, "='", 2);
				write(STDOUT_FILENO, alias->value, _strlen(alias->value));
				write(STDOUT_FILENO, "'\n", 2);
				return;
			}
		}
		alias = alias->next;
	}

	if (name)
	{
		_print_err("alias: ");
		_print_err(name);
		_print_err(" not found\n");
		errno = 1;
	}
}
/**
 * builtin_alias - creates or prints alias
 * @data: program data
 * Return: 0 if successful
 */
int builtin_alias(shell_info *data)
{
	char **args = data->args;
	char *name, *value;
	int i = 0;

	if (args[1] == NULL)
		print_alias(data, NULL);
	else
	{
		i = 1;
		while (args[i] != NULL)
		{
			name = args[i];
			value = strchr(*name == '=' ? name + 1 : args[i], '=');
			if (value != NULL)
			{
				*value = '\0';
				value++;
				add_alias(name, value, data);
			}
			else
			{
				print_alias(data, name);
			}
			i++;
		}
	}
	return (0);
}
