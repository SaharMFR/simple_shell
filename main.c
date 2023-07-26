#include "shell.h"

/**
 * main - The shell loop.
 * @ac: The number of arguments.
 * @av: The list of arguments.
 * @env: The environment.
 * Return: 0 on success, 1 on failure.
 */

int main(__attribute__((unused)) int ac, char **av, char **env)
{
	int bytes;
	size_t size = 10;
	char *command;
	const char delim[4] = " ";
	command = (char *) malloc (size);
	while (command != "exit")
	{
		char *token;
		printf("$ ");
		bytes = getline(&command, &size, stdin);
		if (bytes == -1)
			printf("ERROR!");
		else
		{
			token = strtok(command, delim);
			char *args[10];
			for (int i = 0; i < 10 || token == NULL; i++)
			{
				arr[i] = token;
				token = strtok(NULL, delim);
			}

			if (execve(args[0], args, NULL) == -1)
				printf("ERROR!");
		}
	}
	return (0);
}
