#include "shell.h"

/**
 * main - The start of the program.
 * @ac: The number of arguments.
 * @av: The list of arguments.
 * Return: 0 on success, 1 on failure.
 */

int main(int ac, char **av)
{
	info_t info[] = { SHELL_INIT };
	int fd = 2;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (1);
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	shellLoop(info, av);
	return (0);
}
