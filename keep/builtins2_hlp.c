#include "shell_header.h"

void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

/**
* help_env - Displays information on the shell builtin command 'env'.
*/
void help_env(void)
{
char *msg = "help_env: help_env\n\tDisplays the current environment.\n";

write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
* help_setenv - Displays information on the shell builtin command.
*/
void help_setenv(void)
{
char *msg = "help_setenv: help_setenv [VARIABLE] [VALUE]\n\tInt newenv";

write(STDOUT_FILENO, msg, _strlen(msg));
msg = "\tOn failure, it prints an error message to stderr.\n";
write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
* help_unsetenv - Displays information on the shell builtin command.
*/
void help_unsetenv(void)
{
char *msg = "help_unsetenv: help_unsetenv [VARIABLE]\n\tRemove env";

write(STDOUT_FILENO, msg, _strlen(msg));
msg = "\tOn failure, it prints an error message to stderr.\n";
write(STDOUT_FILENO, msg, _strlen(msg));
}
