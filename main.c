#include "shell.h"

/**
 * sig_handler - Handles the SIGINT signal (Ctrl+C).
 * @sig: The signal number.
 */
void sig_handler(int sig)
{
	/* Handle the SIGINT signal (Ctrl+C). */
	char *prompt = "\n$ ";
	(void)sig;
	signal(SIGINT, sig_handler);
	write(STDIN_FILENO, prompt, 3);
}

/**
 * run_cmd - Executes a command in a child process.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - a corresponding error code.
 *         Otherwise - the exit value of the last executed command.
 */
int run_cmd(char **args, char **front)
{
	/* Execute a command in a child process. */
	pid_t pid;
	int status, flag = 0, ret = 0;
	char *cmd = args[0];

	if (cmd[0] != '/' && cmd[0] != '.')
	{
		flag = 1;
		cmd = get_cmd_location(cmd);
	}

	if (!cmd || access(cmd, F_OK) == -1)
	{
		if (errno == EACCES)
			ret = create_err(args, 126);
		else
			ret = create_err(args, 127);
	}
	else
	{
		pid = fork();
		if (pid == -1)
		{
			if (flag)
				free(cmd);
			perror("Fork failed");
			return (1);
		}
		if (pid == 0)
		{
			execve(cmd, args, environ);
			if (errno == EACCES)
				ret = create_err(args, 126);
			free_env();
			free_args(args, front);
			free_alias_list(aliases);
			_exit(ret);
		}
		else
		{
			wait(&status);
			ret = WEXITSTATUS(status);
		}
	}

	if (flag)
		free(cmd);
	return (ret);
}

/**
 * main - Runs a simple UNIX command interpreter.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: The return value of the last executed command.
 */
int main(int argc, char *argv[])
{
	/* Simple UNIX command interpreter. */
	int ret = 0, exit_status;
	char *prompt = "#sh$ ", *nl = "\n";

	shell_name = argv[0];
	hist_counter = 1;
	aliases = NULL;
	signal(SIGINT, sig_handler);

	exit_status = 0;
	environ = copy_env();
	if (!environ)
		exit(-100);

	if (argc != 1)
	{
		ret = process_file_cmds(argv[1], &exit_status);
		free_env();
		free_alias_list(aliases);
		return (exit_status);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (ret != EOF_SHELL && ret != EXIT_SHELL)
			ret = handle_arguments(&exit_status);
		free_env();
		free_alias_list(aliases);
		return (exit_status);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 5);
		ret = handle_arguments(&exit_status);
		if (ret == EOF_SHELL || ret == EXIT_SHELL)
		{
			if (ret == EOF_SHELL)
				write(STDOUT_FILENO, nl, 1);
			free_env();
			free_alias_list(aliases);
			exit(exit_status);
		}
	}

	free_env();
	free_alias_list(aliases);
	return (exit_status);
}
