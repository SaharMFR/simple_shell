#include "shell.h"

/**
 * get_environ - Gets array copy of our environ.
 * @info: The passed information about the shell.
 * Return: 0.
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->changed_env)
	{
		info->environ = list_to_strings(info->env);
		info->changed_env = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable.
 * @info: The passed information about the shell.
 * @var: the string env var property.
 * Return: 1 on delete, 0 otherwise.
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->changed_env = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->changed_env);
}

/**
 * _setenv - Initializes a new environment variable,
 *             or modify an existing one.
 * @info: The passed information about the shell.
 * @var: the string env var property.
 * @value: the string env var value.
 * Return: 0.
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->changed_env = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->changed_env = 1;
	return (0);
}
