#include "shell.h"

/**
 * _getenv - Gets the value of an environment variable
 * @name: The name of the environment bvariable
 * Return: The value of the environment variable
 */
char *_getenv(const char *name)
{
	size_t name_len = _strlen(name);
	char *value;
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
		{
			value = &environ[i][name_len + 1];
			return (value);
		}
	}
	return (NULL);
}
/**
 * _setenv - adds or modifies an environment variable
 * @var: VARIABLE
 * @val: VALUE
 * Return: 0 if successful, otherwise, -1
 */
int _setenv(char *var, char *val)
{
	char *env;
	int i, len;

	if (!var || !val)
	{
		perror("Invalid argument for setenv\n");
		return (0);
	}

	len = _strlen(var);
	env = malloc(len + _strlen(val) + 2);
	if (!env)
	{
		perror("Allocation error\n");
		exit(EXIT_FAILURE);
	}

	_strcpy(env, var);
	_strcat(env, "=");
	_strcat(env, val);

	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(environ[i], var, len) == 0 && environ[i][len] == '=')
		{
			free(environ[i]);
			environ[i] = env;
			return (0);
		}
	}
	free(environ[i]);
	environ[i] = env;
	environ[i + 1] = NULL;
	return (0);
}
/**
 * _unsetenv - removes or frees environment variable
 * @var: VARIABLE name
 * Return: 0 on success, else -1
 */
int _unsetenv(char *var)
{
	char *env;
	int len;
	int i, found = 0;

	if (!var)
		return (0);

	env = _getenv(var);
	if (!env)
	{
		perror("Variable not found\n");
		return (0);
	}

	len = _strlen(var);

	for (i = 0; environ[i]; i++)
	{
		if (!found)
		{
			if (_strncmp(environ[i], var, len) == 0 && environ[i][len] == '=')
			{
				free(environ[i]);
				found = 1;
			}
			continue;
		}
		environ[i - 1] = environ[i];
	}
	environ[i - 1] = NULL;
	return (0);
}
