#ifndef SHELL_HEADER_H
#define SHELL_HEADER_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

int mul(int, int);
void shell_prompt(char **env);
char *get_path(char **env, char *cmd);
#endif /* SHELL_HEADER_H */
