#include "shell_header.h"

/**
 * main - Entry program
 * @agc: argument count
 * @env: environment
 * Return: Always (Success) 1
 */

int main(int agc, char **env)
{
	if (agc == 1)
		shell_prompt(env);

	return (0);
}
