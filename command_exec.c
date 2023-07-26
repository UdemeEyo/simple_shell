#include "shell_header.h"

/**
 * command_exec - function to execute commands
 * @cmd_arg: command arguments
 * Return: no return
 */

void command_exec(char **cmd_arg)
{
	if (execvp(cmd_arg[0], cmd_arg) == -1)
	{
		char *error_msg = "No such file or directory\n";

		write(STDOUT_FILENO, error_msg, strlen(error_msg));
		exit(EXIT_FAILURE);
	}
}
