#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>

#define MAX_INPUT_LENGTH 1024
void print_prompt(void);
ssize_t read_command(char *buffer);
void execute_command(char *command);


int main(int ac, char **av, char **env);
void cd_prompt(char **av, char **env);

#endif
