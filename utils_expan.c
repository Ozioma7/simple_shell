#include "shell.h"

/**
 * expand_logical_ops - Expands the logical operands in a command
 * @cmd: A command
 * @data: The operation data
 * Return: The ops data
 */
ops_data *expand_logical_ops(char *cmd, ops_data *data)
{
	char *cmd_copy = _strdup(cmd);
	int len = _strlen(cmd_copy);
	int start = 0, idx = 0, oIdx = 0;

	data->operands = calloc(MAX_TOKENS, sizeof(char *));
	if (!data->operands)
	{
		perror("Allocation error");
		exit(EXIT_FAILURE);
	}

	while (*cmd_copy)
	{
		if (_strncmp(cmd_copy, "||", 2) == 0 || _strncmp(cmd_copy, "&&", 2) == 0)
		{
			data->operands[oIdx] = _strdup_range(cmd, start, idx);
			data->operators[oIdx++] = cmd_copy[0] == '|' ? LOGICAL_OR : LOGICAL_AND;
			start = idx + 2;
			cmd_copy += 2;
			idx += 2;
			continue;
		}
		cmd_copy++;
		idx++;
	}
	data->operands[oIdx] = _strdup_range(cmd, start, idx);
	free(cmd_copy - len);
	return (data);
}

/**
 * expand_variables - Expands the variables in a command line
 * @line: The command line
 * @data: The Program data
 * Return: The expanded line
 */
char *expand_variables(char *line, shell_info *data)
{
	char num[10] = {'\0'};
	char *alias;
	char var_buf[MAX_TOKENS] = {'\0'};
	int cIdx = 0, nIdx = 0, i, j, env_found;

	if (!line)
		return (NULL);
	while (*line)
	{
		if (*line == '$' && !(*(line + 1) == ' ' || *(line + 1) == '\0'))
		{
			if (((*(line + 1) == '$') || *(line + 1) == '?'))
			{
				number_to_string(num, *(line + 1) == '$' ? getpid() : errno);
				for (i = 0; num[i]; i++, cIdx++)
					data->cmdlinebuf[cIdx] = num[i];
				line += 2, nIdx += 2;
				continue;
			}
			env_found = 0;
			for (i = 1; *(line + i) && *(line + i) != ' ' && *(line + i) != '$'; i++)
			{
				var_buf[i - 1] = *(line + i), var_buf[i] = '\0', alias = _getenv(var_buf);
				if (alias)
				{
					env_found = 1;
					for (j = 0; alias[j]; j++, cIdx++)
						data->cmdlinebuf[cIdx] = alias[j];
					break;
				}
			}
			line += env_found ? i + 1 : i, nIdx += env_found ? i + 1 : i;
			continue;
		}
		data->cmdlinebuf[cIdx++] = *line;
		nIdx++, line++;
	}
	data->cmdlinebuf[cIdx] = '\0';
	free(line - nIdx);
	return (_strdup(data->cmdlinebuf));
}

/**
 * expand_alias - Expands and alias in a command line
 * @str: Command line
 * @data: Program data
 * @ret: Flag to check if recursive or not
 * Return: The expanded line
 */
char *expand_alias(char *str, int ret, shell_info *data)
{
	char line[4028] = {'\0'}, buf[64] = {'\0'};
	alias_list *alias;
	int i = 0, idx = 0, j = 0;

	while (*str)
	{
		if (*str == ' ')
		{
			buf[i] = '\0';
			alias = get_alias(data, buf);

			if (alias)
			{
				idx -= i;
				line[idx] = '\0';
				_strcat(line, ret ? expand_alias(alias->value, 0, data) : alias->value);
				idx += _strlen(alias->value);
			}
			i = 0;
			while (*str && *str == ' ')
			{
				line[idx++] = *(str++);
				j++;
			}
			line[idx] = '\0';
			continue;
		}

		buf[i] = *str, line[idx] = *str, str++, i++, idx++, j++;
	}
	buf[i] = '\0', alias = get_alias(data, buf);
	if (alias)
	{
		idx -= i;
		line[idx] = '\0';
		_strcat(line, ret ? expand_alias(alias->value, 0, data) : alias->value);
		idx += _strlen(alias->value);
	}
	free(str - j);
	return (_strdup(line));
}
