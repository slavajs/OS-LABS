#ifndef LAB2_UTILS_H
#define LAB2_UTILS_H

#include <iostream>
#include <semaphore.h>


void openShareMemory(int &sfd, std::string name, int oflag, mode_t mode);

void makeMemoryMap(void **var, int prot, int flags, int fd);

void destroySemaphor(sem_t *sem);

void makeMunMap(void *addr);

void unlinkShareMemory(std::string name);

void makeShareMemory(int &sfd, int &semInFd, const std::string &shmName,
               const std::string &semap);

void truncateShareMemory(int &sfd, int &semInFd);

void GetForkError();

char lower(char c);

char replace(char dest, char src);
#endif