#include "shell.h"

/**
 * interactive - Checks if the shell is interactive or not.
 * @info: The passed information about the shell.
 * Return: 1 if the shell is interactive, 0 if not.
 */

int interactive(info_t *info)
{
	return (isattay(STDIN_FILENO) && info->readfd < 3);
}
