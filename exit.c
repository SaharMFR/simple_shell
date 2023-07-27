#include "shell.h"

/**
 * _Estrcpy - Copies a string.
 * @destination: the destination string to be copied to.
 * @source: the source string.
 * @n: the amount of characters to be copied.
 * Return: the concatenated string.
 */
char *_Estrcpy(char *destination, char *source, int n)
{
	int i, j;
	char *s = destination;

	i = 0;
	while (source[i] != '\0' && i < n - 1)
	{
		destination[i] = source[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * _Estrcat - concatenates two strings
 * @destination: the first string
 * @source: the second string
 * @n: the amount of bytes to be maximally used
 * Return: the concatenated string
 */
char *_Estrcat(char *destination, char *source, int n)
{
	int i, j;
	char *s = destination;

	i = 0;
	j = 0;
	while (destination[i] != '\0')
		i++;
	while (source[j] != '\0' && j < n)
	{
		destination[i] = source[j];
		i++;
		j++;
	}
	if (j < n)
		destination[i] = '\0';
	return (s);
}

/**
 * _Estrchr - locates a character in a string
 * @str: the string to be parsed
 * @c: the character to look for
 * Return: (str) a pointer to the memory area s
 */
char *_Estrchr(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
