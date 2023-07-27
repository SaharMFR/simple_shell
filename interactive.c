#include "shell.h"

/**
 * interactive - Checks if the shell is interactive or not.
 * @info: The passed information about the shell.
 * Return: 1 if the shell is interactive, 0 if not.
 */

int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd < 3);
}

/**
 * is_delim - Checks if character is a delimeter.
 * @c: The char to check.
 * @delim: The delimeter string.
 * Return: 1 if true, 0 if false.
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - Checks if alphabetic character.
 *@character: The character to be checked.
 *Return: 1 if c is alphabetic, 0 otherwise.
 */

int _isalpha(int character)
{
	if ((character >= 'a' && character <= 'z')
			|| (character >= 'A' && character <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - Converts a string to an integer.
 *@str: The string to be converted.
 *Return: Converted number, 0 if no numbers in string.
 */

int _atoi(char *str)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
