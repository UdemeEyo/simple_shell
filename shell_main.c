#include "shell_header.h"

/**
 * main - Entry program
 * @agc: argument count
 * @agv: argument vector
 * @env: environment
 * Return: Always (Success) 1
 */
int main(int agc, char **agv, char **env)
{
	if (agc == 1)
		shell_prompt(agv, env);

	return (0);
}
