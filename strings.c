#include "shell.h"

/**
 * _strlen - Evaluates the length of a string
 * @str: The string
 * Return: The length of the string
 */
size_t _strlen(const char *str)
{
	size_t len = 0;

	while (str[len] != '\0')
		len++;
	return (len);
}

/**
 * _strcpy - Copy a memory area of `src` into `dest`
 * @dest: The destination memeory area
 * @src: The source to copy from
 * Return: Pointer to the dest memory area
 */
char *_strcpy(char *dest, const char *src)
{
	size_t i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcat - Add memory area of `src` to `dest`
 * @dest: The destination memeory area
 * @src: The source to copy from
 * Return: Pointer to the dest memory area
 */
char *_strcat(char *dest, const char *src)
{
	size_t dest_len = _strlen(dest);
	size_t i = 0;

	while (src[i] != '\0')
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest);
}

/**
 * _strncmp - Checks if `n` characters of two strings matches
 * @s1: The first string
 * @s2: The second string
 * @n: The number of characters to match
 * Return: 0 if they match else the lexicological
 * difference between `s1` and `s2` at the index of
 * mismatch
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i = 0;

	while (s1[i] != '\0' && s2[i] != '\0' && i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (i == n)
		return (0);
	return (s1[i] - s2[i]);
}
/**
 * _strdup - Duplicates a string
 * @str: The string to duplicate
 * Return: A pointer to the duplicated string, or NULL on failure
 */
char *_strdup(const char *str)
{
	char *dup;
	size_t len;

	if (str == NULL)
		return (NULL);
	len = _strlen(str) + 1;
	dup = malloc(len);

	if (!dup)
		return (NULL);
	_strcpy(dup, str);
	return (dup);
}
