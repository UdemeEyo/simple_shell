#ifndef SHELL_HEADER_H
#define SHELL_HEADER_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

int mul(int, int);
void shell_prompt(char **env);

#endif /* SHELL_HEADER_H */
