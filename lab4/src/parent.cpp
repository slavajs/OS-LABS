#include "parent.h"
#include "utils.h"
#include <sys/mman.h>
#include <unistd.h>


constexpr auto FIRST_SHM_NAME = "shared_memory_first"; 
constexpr auto SECOND_SHM_NAME = "shared_memory_second"; 
constexpr auto THIRD_SHM_NAME = "third_shared_memory"; 
constexpr auto FIRST_SEMAP = "first_semaphore"; 
constexpr auto SECOND_SEMAP = "second_semaphore";
constexpr auto THIRD_SEMAP = "third_semaphore";


std::vector<std::string> ParentRoutine(char const *pathToChild1, char const *pathToChild2,
                                       const std::vector<std::string> &input) {

    std::vector<std::string> output;

    int sfd1, semFd1;
    makeShareMemory(sfd1, semFd1, FIRST_SHM_NAME, FIRST_SEMAP);
    truncateShareMemory(sfd1, semFd1);
    sem_t *sem1 = nullptr;
    makeMemoryMap((void **) &sem1, PROT_WRITE | PROT_READ, MAP_SHARED, semFd1);
    sem_init(sem1, 1, 0);


    int sfd2, semFd2;
    makeShareMemory(sfd2, semFd2, SECOND_SHM_NAME, SECOND_SEMAP);
    truncateShareMemory(sfd2, semFd2);
    sem_t *sem2 = nullptr;
    makeMemoryMap((void **) &sem2, PROT_WRITE | PROT_READ, MAP_SHARED, semFd2);
    sem_init(sem2, 1, 0);


    int pid = fork();


    if (pid == 0) {
        if (execl(pathToChild1, FIRST_SHM_NAME, FIRST_SEMAP,
                  THIRD_SHM_NAME, THIRD_SEMAP, nullptr) == -1) {
            std::cout << "Error executin file\n";
        }
    } else if (pid == -1) {
        GetForkError();
    } else {
        char *ptr;
        makeMemoryMap((void **) &ptr, PROT_READ | PROT_WRITE, MAP_SHARED, sfd1);
        for (const std::string &s: input) {
            sprintf((char *) ptr, "%s", s.c_str());
            ptr += s.size() + 1;
            sem_post(sem1);
        }
        sprintf((char *) ptr, "%s", "");
        sem_post(sem1);

        int sfd3, semFd3;
        makeShareMemory(sfd3, semFd3, THIRD_SHM_NAME, THIRD_SEMAP);
        truncateShareMemory(sfd3, semFd3);
        sem_t *sem3 = nullptr;
        makeMemoryMap((void **) &sem3, PROT_WRITE | PROT_READ, MAP_SHARED, semFd3);
        sem_init(sem3, 1, 0);


        pid = fork();

        if (pid == 0) {
            if (execl(pathToChild2, THIRD_SHM_NAME, THIRD_SEMAP,
                      SECOND_SHM_NAME, SECOND_SEMAP, nullptr) == -1) {
                std::cout << "Error executin file\n";
            }
        } else if (pid == -1) {
            GetForkError();
        } else { 
            char *ptr2;
            makeMemoryMap((void **) &ptr2, PROT_READ | PROT_WRITE, MAP_SHARED, sfd2);

            while (true) {
                sem_wait(sem2);
                std::string s = std::string(ptr2);
                ptr2 += s.size() + 1;
                if (s.empty()) {
                    break;
                }
                output.push_back(s);
            }
            destroySemaphor(sem1);
            makeMunMap(sem1);
            destroySemaphor(sem2);
            makeMunMap(sem2);

            unlinkShareMemory(FIRST_SHM_NAME);
            unlinkShareMemory(SECOND_SHM_NAME);
            unlinkShareMemory(FIRST_SEMAP);
            unlinkShareMemory(SECOND_SEMAP);
        }
    }
    return output;
}
