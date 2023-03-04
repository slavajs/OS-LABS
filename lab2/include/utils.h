#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#ifndef UTILS_H
#define UTILS_H

void toLower(char *string);
void replaceChar(char *string, char c1, char c2);
int strLen(char * string);
void create_pipe(int fd[]);
void duplicate(int old, int newDup);
#endif