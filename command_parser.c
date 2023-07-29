#include "shell_header.h"

/**
 * command_parser - parses command from stdin
 * to tokens
 * @str: input string
 * @cmd_arg: array of tokens
 * Return: no return
 */

void command_parser(char *str, char **cmd_arg)
{
	int a = 0, b = 0;

	while (str[a])
	{
		if (str[a] == '\n')
			str[a] = 0;
		a++;
	}

	cmd_arg[0] = strtok(str, " ");
	while (cmd_arg[b])
		cmd_arg[++b] = strtok(NULL, " ");
}
