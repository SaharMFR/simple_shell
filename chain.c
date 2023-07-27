#include "shell.h"

/**
 * is_chain - Checks if the current char in buffer is a chain delimeter.
 * @info: The passed information about the shell.
 * @buffer: The char buffer.
 * @pos: The address of the current position in the buffer.
 * Return: 1 if chain delimeter, 0 otherwise.
 */
int is_chain(info_t *info, char *buffer, size_t *pos)
{
	size_t j = *pos;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		info->cmd_type = 1;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		info->cmd_type = 2;
	}
	else if (buffer[j] == ';')
	{
		buffer[j] = 0;
		info->cmd_type = 3;
	}
	else
		return (0);
	*pos = j;
	return (1);
}

/**
 * check_chain - Checks if we should continue chaining based on last status.
 * @info: The passed information about the shell.
 * @buffer: The char buffer.
 * @pos: The address of the current position in the buffer.
 * @start: The starting position in the buffer.
 * @len: The length of the buffer.
 */
void check_chain(info_t *info, char *buffer,
		size_t *pos, size_t start, size_t len)
{
	size_t j = *pos;

	if (info->cmd_type == 2)
	{
		if (info->status)
		{
			buffer[start] = 0;
			j = len;
		}
	}
	if (info->cmd_type == 1)
	{
		if (!info->status)
		{
			buffer[start] = 0;
			j = len;
		}
	}

	*pos = j;
}

/**
 * replace_alias - Replaces an aliases in the tokenized string.
 * @info: The passed information about the shell.
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _Estrchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - Replaces vars in the tokenized string.
 * @info: The passed information about the shell.
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
				_strdup(_Estrchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - Replaces a string.
 * @old: The address of the old string.
 * @new: The new string.
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
