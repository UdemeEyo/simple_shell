#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "shell.h"

/**
* print_prompt - Display the shell prompt
*/
void print_prompt(void)
{
	write(STDOUT_FILENO, "$ ", 2);
}

/**
* read_command - Read a command from the user
* @buffer: Buffer to store the input command
* Return: The number of characters read
*/
ssize_t read_command(char *buffer)
{
	ssize_t n_chars = getline(&buffer, &(size_t){MAX_INPUT_LENGTH}, stdin);

	if (feof(stdin))
		exit(EXIT_SUCCESS);
	perror("Error reading command");
	exit(EXIT_FAILURE);
}
	return (n_chars);
}

/**
 * execute_command - Execute a command in the shell
 * @command: The command to be executed
 */
void execute_command(char *command)
{
	char *argv[] = {command, NULL};
	extern char **env;

	pid_t pid = fork();
	if (pid == -1)
{
	perror("Fork failed");
	return;
}
else if (pid == 0)
{
	execve(command, argv, env);
perror("Executon failed");
exit(EXIT_FAILURE);
}
else
{
	waitpid(pid, NULL, 0);
}
}

/**
 * main - executes code
 * Return: integer
 */
int main(void)
{
	char *buffer = NULL;
	size_t buffer_size = 0;

	while (1)
{
	print_prompt();
	ssize_t n_chars = read_command(buffer);
if (n_chars <= 1)
continue;
/*remove newline character*/
buffer[n_chars - 1] = '\0';

execute_command(buffer);
}
	free(buffer);
return (0);
}
