#include <sys/wait.h>
#include "shell_header.h"
#include <string.h>
#include <unistd.h>

/**
 * shell_prompt - function that runs the simple shell
 * @agv: argument vector
 * @env: environment variable
 * Return: no return
 */
void shell_prompt(char **env)
{
	char *str = NULL;
	int a = 0, stat;
	size_t num = 0;
	ssize_t numChar;
	char *argv[] = {NULL, NULL};
	pid_t pid_child;

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
			{
				char *error_msg = "No such file or directory\n";
				write(STDOUT_FILENO, error_msg, strlen(error_msg));
			}
		}
		else
			wait(&stat);
	}
}
