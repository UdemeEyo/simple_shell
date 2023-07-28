#ifndef SHELL_HEADER_H
#define SHELL_HEADER_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int mul(int, int);
int shell_prompt(char **argv, char **env);

/*stdin formatting*/
void command_parser(char *str, char **cmd_arg);
void command_exec(char **argv, char **env);

/*builtins*/
void all_cmd(void);
void alias_cmd(void);
void cd_cmd(void);
void exit_cmd(void);
void help_cmd(void);

void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

/*env_builtins*/
int _setenv(char **args, char __attribute__((__unused__)) **front);
int _unsetenv(char **args, char __attribute__((__unused__)) **front);
int _env(char **args, char __attribute__((__unused__)) **front);

/*ex_builtins*/
int handle_alias(char **args, char __attribute__((__unused__)) **front);
void set_alias_value(char *alias_name, char *alias_value);
/* void print_aliases(alias_t *alias_list); */

#endif /* SHELL_HEADER_H */
