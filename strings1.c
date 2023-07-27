#include "shell.h"

/**
 * _strlen - Calculates the length of a string.
 * @str: The string, to find its length.
 * Return: The length of string.
 */
int _strlen(char *str)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str++)
		i++;
	return (i);
}

/**
 * _strcmp - Compares between two strings.
 * @str1: The first string.
 * @str2: The second string.
 * Return: Negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * starts_with - checks if a string starts with substring.
 * @str: The string to search in.
 * @toFind: The substring to find
 * Return: The address of next char of 'str' or NULL
 */
char *starts_with(const char *str, const char *toFind)
{
	while (*toFind)
		if (*toFind++ != *str++)
			return (NULL);
	return ((char *)str);
}

/**
 * _strcat - Concatenates two strings.
 * @destination: The destination buffer.
 * @source: The source buffer.
 * Return: Pointer to destination buffer.
 */
char *_strcat(char *destination, char *source)
{
	char *ret = destination;

	while (*destination)
		destination++;
	while (*source)
		*destination++ = *source++;
	*destination = *source;
	return (ret);
}
