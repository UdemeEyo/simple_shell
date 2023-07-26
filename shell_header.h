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
void command_parser(char *str, char **cmd_arg);
void command_exec(char **cmd_arg);

#endif /* SHELL_HEADER_H */
