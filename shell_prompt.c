#include "shell_header.h"
#include <sys/wait.h>

/**
 * shell_prompt - functiont that runs the simple shell
 * @agv: argument vector
 * @env: environment variable
 * Return: no return
 */

void shell_prompt(char **agv, char **env)
{
	char *str = NULL;
	int a = 0, stat;
	size_t num = 0;
	ssize_t numChar;
	char *argv[] = {NULL, NULL};
	pid_t pid_child;

	while (1)
	{
		printf("D-UShell$ ");

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

		argv[0] = str;
		pid_child = fork();
		if (pid_child == -1)
		{
			free(str);
			exit(EXIT_FAILURE);
		}
		if (pid_child == 0)
		{
			if (execve(argv[0], argv, env) == -1)
				printf("%s No such file or directory\n", agv[0]);
		}
		else
			wait(&stat);
	}
}
