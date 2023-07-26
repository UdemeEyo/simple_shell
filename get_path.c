#include "shell_header.h"
#include <stdlib.h>
#include <string.h>

/**
 * get_path - function that searches path directories for command
 * @env: env variable
 * @cmd: command to find
 * Return: full path to command if found, otherwise NULL
 */
char *get_path(char **env, char *cmd)
{
	char *path = NULL, *dir, *full_path;
	int i = 0;

	while (env[i])
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
		{
			path = env[i] + 5;
			break;
		}
		i++;
	}

	if (path == NULL)
		return (NULL);

	dir = strtok(path, ":");
	while (dir != NULL)
	{
	if (*dir != '\0')
	{
		full_path = malloc(strlen(dir) + strlen(cmd) + 2);
		if (full_path == NULL)
			exit(EXIT_FAILURE);

		strcpy(full_path, dir);
		strcat(full_path, "/");
		strcat(full_path, cmd);

		if (access(full_path, X_OK) == 0)
			return (full_path);

		free(full_path);
	}
		dir =(char *)strtok(NULL, ":");
	}
	return (NULL);
}
