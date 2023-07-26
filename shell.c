#include <sys/wait.h>
#include "shell_header.h"
#include <string.h>
#include <unistd.h>
#define MAXCD 10
/**
 * shell_prompt - function that runs the simple shell
 * @agv: argument vector
 * @env: environment variable
 * Return: no return
 */
void shell_prompt(char **env)
{
	char *str = NULL;
	int a, b, stat;
	size_t num = 0;
	ssize_t numChar;
	char *argv[MAXCD];
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
		a = 0;
		while (str[a])
		{
			if (str[a] == '\n')
				str[a] = 0;
			a++;
		}
		b = 0;
		argv[0] = strtok(str, " ");
		while (argv[b])
		{
			argv[++b] = strtok(NULL, " ");
		}
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
