#include "shell.h"

/**
 * _strcmp - compares strings
 * @s1: string 1
 * @s2: string 2
 * Return: 0 or difference
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}

	return (0);
}

/**
 * _strtok - Splits a string into tokens returning a turn a time
 * @str: String to tokenize
 * @delim: The delimiter to use
 * Return: a token or NULL
 */
char *_strtok(char *str, char *delim)
{
	static char *s;
	int dIdx; /* Delimiter index */
	char *token;

	if (str != NULL)
		s = str;
	if (!delim)
		return (NULL);
	while (*s != '\0')
	{
		dIdx = 0;
		while (delim[dIdx] != '\0')
		{
			if (*s == delim[dIdx])
				break;
			dIdx++;
		}
		if (!delim[dIdx])
			break;
		s++;
	}
	token = s;
	if (*token == '\0')
		return (NULL);
	while (*s != '\0')
	{
		dIdx = 0;
		while (delim[dIdx] != '\0')
		{
			if (*s == delim[dIdx])
			{
				*s = '\0';
				s++;
				return (token);
			}
			dIdx++;
		}
		s++;
	}
	return (token);
}

/**
 * _strdup_range - Duplicates a range of a string
 * @src: The string
 * @from: The start index (inclusive)
 * @to: The end index (exclusive)
 * Return: The new string
 */
char *_strdup_range(char *src, int from, int to)
{
	int i = 0;
	char *dup;

	dup = malloc((to - from + 2) * sizeof(char));
	if (!dup)
	{
		perror("Allocation error");
		exit(EXIT_FAILURE);
	}

	while (from < to)
		dup[i++] = src[from++];
	dup[i] = '\0';
	return (dup);
}

/**
 * _strtrim - Removes beginning trailing whitespace
 * @str: The string to trim
 * Return: The trimmed string
 */
char *_strtrim(char *str)
{
	char *dup = _strdup(str);
	int i = 0;

	while (*dup == ' ')
		dup++, i++;
	_strcpy(str, dup);

	free(dup - i);
	return (str);
}

/**
 * _isdigit - Checks if a string contains onl digits
 * @s: String to check
 * Return: 1 if true else 0
 */
int _isdigit(char *s)
{

	int i = 0;

	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
