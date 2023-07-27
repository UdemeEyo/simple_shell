#include "shell_header.h"

#define MAXCD 10
/**
 * shell_prompt - function that runs the simple shell
 * @str: input string
 * @cmd_arg: command arguments
 * Return: no return
 */
void command_parser(char *str, char **cmd_arg);
void command_exec(char **cmd_arg);

int shell_prompt(void)
{
	char *str = NULL;
	int stat;
	size_t num = 0;
	ssize_t numChar;
	char *cmd_arg[MAXCD];
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
		command_parser(str, cmd_arg);

		pid_child = fork();
		if (pid_child == -1)
		{
			free(str);
			exit(EXIT_FAILURE);
		}
		if (pid_child == 0)
		{
			command_exec(cmd_arg);
		}
		else
			wait(&stat);
	}
}
