#include "../include/utils.h"
#include "../include/parent.h"

#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

void ParentRoutine(FILE *stream, FILE* outputStream)
{
    long long counter = 0;
    int FIRST_PIPE[2];
    int PIPE_BETWEEN_PROCESSES[2];
    create_pipe(FIRST_PIPE);
    create_pipe(PIPE_BETWEEN_PROCESSES);
    int id1 = fork();
    if (id1 == 0)
    {
        duplicate(FIRST_PIPE[0], STDIN_FILENO);
        duplicate(PIPE_BETWEEN_PROCESSES[1], STDOUT_FILENO);
        close(FIRST_PIPE[1]);
        close(PIPE_BETWEEN_PROCESSES[0]);
        close(FIRST_PIPE[0]);
        close(FIRST_PIPE[1]);
        char *argv[3];
        // argv[0] = getenv("child1");
        argv[0] = "/home/dmimalek/labs/OS/build/lab2/child1";
        argv[1] = NULL;
        if (execv("/home/dmimalek/labs/OS/build/lab2/child1", argv) == -1)
        {
            printf("Failed to execute child process 1\n");
            exit(EXIT_FAILURE);
        }

    }
    else if (id1 > 0)
    {
        close(FIRST_PIPE[0]);
        char *string = NULL;
        size_t len;
        int flag = 0;
        while ((flag = getline(&string, &len, stream)) != -1) {   
            // write(FIRST_PIPE[1], string, strlen(string) + 1);
            if (string[len-1] != '\n') {
                char ch[] = "\n";
                write(FIRST_PIPE[1], string, strlen(string) - 1);
                write(FIRST_PIPE[1], &ch, 1);
                write(FIRST_PIPE[1], &string[len], 1);
            } else {
                write(FIRST_PIPE[1], string, strlen(string) + 1);
            }
            counter++;
        }
        if (string != NULL) {
                free(string);
        }
        close(FIRST_PIPE[1]);
        int SECOND_PIPE[2];
        create_pipe(SECOND_PIPE);
        int id2 = fork();
        if (id2 == 0)
        {
            char *argv[2];
            // argv[0] = getenv("child2");
            argv[0] = "/home/dmimalek/labs/OS/build/lab2/child2";
            argv[1] = NULL;
            close(SECOND_PIPE[0]);
            close(PIPE_BETWEEN_PROCESSES[1]);
            dup2(PIPE_BETWEEN_PROCESSES[0], STDIN_FILENO);
            dup2(SECOND_PIPE[1], STDOUT_FILENO);
            if (execv("/home/dmimalek/labs/OS/build/lab2/child2", argv) == -1)
            {
                printf("Failed to execute child process 2\n");
                exit(EXIT_FAILURE);
            }
            close(PIPE_BETWEEN_PROCESSES[0]);
            close(SECOND_PIPE[1]);
            close(SECOND_PIPE[0]);
        }
        else if (id2 > 0)
        { // parent
            close(SECOND_PIPE[1]);
            close(PIPE_BETWEEN_PROCESSES[0]);
            close(PIPE_BETWEEN_PROCESSES[1]);
            wait(NULL);
            // printf("%lld\n", counter);
            for (int i = 0;i < counter; i++) {
                char ch;
                while(read(SECOND_PIPE[0], &ch, 1)) {
                    // printf("%c", ch);
                    putc(ch, outputStream);
                    if (ch == '\n') {
                        break;
                    }
                }
            }
            close(SECOND_PIPE[0]);
        }
    }
}