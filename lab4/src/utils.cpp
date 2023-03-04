#include "utils.h"
#include <sys/mman.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>


void openShareMemory(int &sfd, std::string name, int oflag, mode_t mode) {
    if ((sfd = shm_open(name.c_str(), oflag, mode)) == -1) {
        std::cout << "Error opening share memory" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void makeMemoryMap(void **var, int prot, int flags, int fd) {
    *var = mmap(nullptr, getpagesize(), prot, flags, fd, 0);
    if (var == MAP_FAILED) {
        std::cout << "Error making munmap" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void destroySemaphor(sem_t *sem) {
    if (sem_destroy(sem) == -1) {
        std::cout << "Error destroying sem" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void makeMunMap(void *addr) {
    if (munmap(addr, getpagesize()) == -1) {
        std::cout << "Munmap making error" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void unlinkShareMemory(std::string name) {
    if (shm_unlink(name.c_str()) == -1) {
        std::cout << "Error unlinking share memory" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void makeShareMemory(int &sfd, int &semInFd, const std::string &shmName,
               const std::string &semap) {
    openShareMemory(sfd, shmName, O_CREAT | O_RDWR, S_IRWXU);
    openShareMemory(semInFd, semap, O_CREAT | O_RDWR, S_IRWXU);
}

void truncateShareMemory(int &sfd, int &semInFd){
    ftruncate(sfd, getpagesize());
    ftruncate(semInFd, getpagesize());
}

void GetForkError() {
    std::cout << "Error forking process" << std::endl;
    exit(EXIT_FAILURE);
}
char lower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c +'a'-'A';
    }
    else {
        return c;
    }
}


