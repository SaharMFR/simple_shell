#include "shell.h"

/**
 *_eputs - Prints the string input.
 * @str: The string to be printed.
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - Writes the passed character to stderr.
 * @c: The character to be printed.
 * Return: 1 on success, -1 otherwise.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[1024];

	if (c == -1 || i >= 1024)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != -1)
		buf[i++] = c;
	return (1);
}

/**
 * _erratoi - Converts a string to integer.
 * @str: The string to be converted.
 * Return: Converted number, 0 if no numbers in the string,
 *       -1 on failure.
 */
int _erratoi(char *str)
{
	int i = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;
	for (i = 0;  str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result *= 10;
			result += (str[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - Prints the error message.
 * @info: The passed information about the shell.
 * @error: The error (specific type).
 */
void print_error(info_t *info, char *error)
{
	_eputs(info->fileName);
	_eputs(": ");
	print_d(info->nLine, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(error);
}

/**
 * print_d - Prints a decimal integer.
 * @input: The input.
 * @fd: The file descriptor to write to.
 * Return: The number of printed characters.
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}
