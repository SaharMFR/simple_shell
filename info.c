#include "shell.h"

/**
 * clear_info - Initializes info_t struct
 * @info: The passed information about the shell.
 */
void clear_info(info_t *info)
{
	info->args = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - Initializes info_t struct.
 * @info: The passed information about the shell.
 * @av: argument vector.
 */
void set_info(info_t *info, char **av)
{
	int i = 0;

	info->fileName = av[0];
	if (info->args)
	{
		info->argv = strtoken(info->args, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->args);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - Frees info_t struct fields.
 * @info: The passed information about the shell.
 * @all: true if required to free all fields.
 */
void free_info(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->args);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(-1);
	}
}
