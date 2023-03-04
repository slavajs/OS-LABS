#include "utils.h"
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cout << "Wrong number of arguments in child2\n";
        exit(EXIT_FAILURE);
    }

    int readFd, semInFd;
    openShareMemory(readFd, argv[0], O_CREAT | O_RDWR, S_IRWXU);
    openShareMemory(semInFd, argv[1], O_CREAT | O_RDWR, S_IRWXU);

    int writeFd, semOutFd;
    openShareMemory(writeFd, argv[2], O_CREAT | O_RDWR, S_IRWXU);
    openShareMemory(semOutFd, argv[3], O_CREAT | O_RDWR, S_IRWXU);


    char *input, *output;
    sem_t *semInput, *semOutput;
    makeMemoryMap((void **) &input, PROT_READ | PROT_WRITE, MAP_SHARED, readFd);
    makeMemoryMap((void **) &output, PROT_READ | PROT_WRITE, MAP_SHARED, writeFd);
    makeMemoryMap((void **) &semInput, PROT_READ | PROT_WRITE, MAP_SHARED, semInFd);
    makeMemoryMap((void **) &semOutput, PROT_READ | PROT_WRITE, MAP_SHARED, semOutFd);



    char *ptrIn = input, *ptrOut = output;

    while (true) {
        sem_wait(semInput);
        std::string s = std::string(ptrIn);
        ptrIn += s.size() + 1;
        if (s.empty()) {
            break;
        }
        for (size_t i = 0; i < s.size(); i++) {
            if (s[i] == ' ') {
                s[i] = '_';
            }
        }
        sprintf((char *) ptrOut, "%s", s.c_str());
        ptrOut += s.size() + 1;
        sem_post(semOutput);
    }

    sprintf((char *) ptrOut, "%s", "");
    sem_post(semOutput);

    makeMunMap(input);
    makeMunMap(output);
    makeMunMap(semInput);
    makeMunMap(semOutput);
    return 0;
}