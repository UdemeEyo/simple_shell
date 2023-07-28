#include "shell_header.h"
void command_parser(char *str, char **cmd_arg);
void command_exec(char **argv, char **env);
#define MAXCD 10
/**
 * shell_prompt - function that runs the simple shell
 * @argv: argument vector
 * @env: environment variable
 * Return: no return
 */

int shell_prompt(char **argv, char **env)
{
	char *str = NULL;
	int stat;
	size_t num = 0;
	ssize_t numChar;
	char *cmd_arg[MAXCD];
	pid_t pid_child;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "D-UShell$ ", 10);

		if (!argv)
			return (-1);

		numChar = getline(&str, &num, stdin);
		if (numChar == -1)
		{
			free(str);
			exit(EXIT_FAILURE);
		}
		command_parser(str, cmd_arg);

		pid_child = fork();
		if (pid_child == -1)
		{
			free(str);
			exit(EXIT_FAILURE);
		}
		if (pid_child == 0)
			command_exec(cmd_arg, env);
		else
			wait(&stat);
	}
}
