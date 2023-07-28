#include "shell_header.h"

/**
 * main - Entry program
 * @argc: argument count
 * @argv: argument vector
 * @env: environment
 * Return: Always (Success) 1
 */
int main(int argc, char **argv, char **env)
{
	if (argc == 1)
		shell_prompt(argv, env);

	return (0);
}
