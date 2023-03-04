#include "../include/utils.h"

char lower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c +'a'-'A';
    }
    else {
        return c;
    }
}
void toLower(char *string) {
    int n = strLen(string);
    for (int i = 0; i < n;i++) {
        string[i] = lower(string[i]);
    }
}

void replaceChar(char *string, char c1, char c2) {
    int len = strLen(string);
    for (int i = 0; i < len; i++) {
        if (string[i] == c1) {
            string[i] = c2;
        }
    }
}


int strLen(char * string) {
    int counter = 0;
    while (string[counter] != '\0') {
        counter++;
    }
    return counter;
}
void create_pipe(int fd[]) {
    int res = pipe(fd);
    if (res !=0) {
        printf("Error creating pipe\n");
        exit(EXIT_FAILURE);
    }

}

void duplicate(int old, int newDup) {
    if (dup2(old, newDup) == -1) {
        printf("dup2 error");
    }
}