#include "shell.h"

/**
 * number_to_string - Converts a number to string
 * @buf: Buffer to store the string version
 * of the number
 * @num: The number to convert
 * Return: Void
 */
void number_to_string(char *buf, int num)
{
	int i = 0;

	if (num == 0)
	{
		buf[0] = '0', buf[1] = '\0';
		return;
	}

	while (num)
	{
		buf[i++] = '0' + (num % 10);
		num /= 10;
	}
	reverse_string(buf);
}

/**
 * reverse_string - Reverses a string in place
 * @str: string to be reversed
 * Retunr: Void
 */
void reverse_string(char *str)
{
	int len = _strlen(str), i = 0;
	char *dup = malloc(sizeof(char) * len + 1);

	_strcpy(dup, str);

	while (--len >= 0)
	{
		str[i++] = dup[len];
	}
	free(dup);
}
/**
 * _atoi - converts a string to an integer
 * @str: string
 * Return: integer
 */
int _atoi(char *str)
{
	int sign = 1, i = 0, result = 0;

	if (str[0] == '-')
	{
		sign *= -1;
		i = 1;
	}
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			result = (result * 10) + (str[i] - '0');
		i++;
	}
	result *= sign;
	return (result);
}
