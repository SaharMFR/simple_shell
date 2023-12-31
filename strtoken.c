#include "shell.h"

/**
 * strtoken - Splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @delim: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtoken(char *str, char *delim)
{
	int i, j, k, m, numWords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], delim) && (is_delim(str[i + 1], delim) || !str[i + 1]))
			numWords++;

	if (numWords == 0)
		return (NULL);
	s = malloc((1 + numWords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numWords; j++)
	{
		while (is_delim(str[i], delim))
			i++;
		k = 0;
		while (!is_delim(str[i + k], delim) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strtoken2 - splits a string into words
 * @str: the input string
 * @delim: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtoken2(char *str, char delim)
{
	int i, j, k, m, numWords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != delim && str[i + 1] == delim) ||
		    (str[i] != delim && !str[i + 1]) || str[i + 1] == delim)
			numWords++;
	if (numWords == 0)
		return (NULL);
	s = malloc((1 + numWords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numWords; j++)
	{
		while (str[i] == delim && str[i] != delim)
			i++;
		k = 0;
		while (str[i + k] != delim && str[i + k] && str[i + k] != delim)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
