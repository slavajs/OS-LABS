// var 13

#include "../include/utils.h"
#include <ctype.h>
#include "stdlib.h"


int main() {
    char *string = NULL;
    size_t len = 0;
    int flag;
    while((flag = getline(&string, &len, stdin)) != -1) {
        toLower(string);
        printf("%s", string);
    }
    if (string != NULL) {
        free(string);
    }
    return 0;
}