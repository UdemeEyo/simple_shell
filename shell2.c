#include <sys/types.h>
#include <sys/wait.h>
#include "shell_header.h"
#include <string.h>
#include <stdlib.h>

#define MAX_CD 10
/**
 * shell_prompt - function that runs the simple shell
 * @env: environment variable
 * Return: no return
 */
void shell_prompt(char **env)
{
	char *str = NULL;
	int a = 0, stat, arg_count;
	size_t num = 0;
	ssize_t numChar;
	char *argv[MAX_CD];
	pid_t pid_child;
	char *token;

	while (1)
	{
		write(STDOUT_FILENO, "D-UShell$ ", 10);

	numChar = getline(&str, &num, stdin);
		if (numChar == -1)
		{
			free(str);
			exit(EXIT_FAILURE);
		}

		while (str[a])
		{
			if (str[a] == '\n')
				str[a] = 0;
			a++;
		}

		arg_count = 0;
		char *token = strtok(str, " ");
		while (token != NULL && arg_count < MAX_CD - 1)
		{
			argv[arg_count++] = token;
			token = strtok(NULL, " ");
		}
		argv[arg_count] = NULL; /* Set the last element to NULL */

		pid_child = fork();
		if (pid_child == -1)
		{
			free(str);
			exit(EXIT_FAILURE);
		}
		if (pid_child == 0)
		{
			if (execve(argv[0], argv, env) == -1)
			{
				char *error_msg = "Error executing command\n";
				write(STDOUT_FILENO, error_msg, strlen(error_msg));
			}
		}
		else
			wait(&stat);
	}
}
