#include "shell.h"

/**
 * shellLoop - The main shell loop.
 * @info: The passed information about the shell.
 * @av: The argument vector passed from main function.
 * Return: 0 on success, 1 on error.
 */
int shellLoop(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(-1);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->errNum == -1)
			exit(info->status);
		exit(info->errNum);
	}
	return (builtin_ret);
}

/**
 * find_builtin - Finds the built-in command.
 * @info: The passed information about the shell.
 * Return: 0 on success, -1 if the built-in function was not found,
 *	1 if it was found but not successful, -2 if built-in signals exit().
 */
int find_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].command; i++)
	{
		if (_strcmp(info->argv[0], builtintbl[i].command) == 0)
		{
			info->nLine++;
			built_in_ret = builtintbl[i].fun(info);
			break;
		}
	}
	return (built_in_ret);
}

/**
 * find_cmd - Finds the command in PATH.
 * @info: The passed information about the shell.
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->inputLine == 1)
	{
		info->nLine++;
		info->inputLine = 0;
	}
	for (i = 0, k = 0; info->args[i]; i++)
		if (!is_delim(info->args[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->args) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - Forks an executive thread to run cmd.
 * @info: The passed information about the shell.
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
