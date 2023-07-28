#include "shell_header.h"

/**
 * command_exec - function to execute commands
 * @argv: argument vector
 * @env: environment vector
 * Return: no return
 */

void command_exec(char **argv, char **env)
{
	if (execve(argv[0], argv, env) == -1)
	{
		char *error_msg = "No such file or directory\n";

		write(STDOUT_FILENO, error_msg, strlen(error_msg));
		exit(EXIT_FAILURE);
	}
}
