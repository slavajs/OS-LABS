#ifndef BITONIC_H
#define BITONIC_H
#include "pthread.h"

#define UP 1
#define DOWN 0

typedef struct ArgsBitonic{
    int *array;
    int size;
    int start;
    int dir;
}ArgsBitonic;

void InitArgs(ArgsBitonic *args, int *array, int size, int start, int dir);
void Comparator(int *array, int i, int j, int dir);
void BitonicMergeSinglThread(ArgsBitonic *arg);
void BitonicSortSinglThread(ArgsBitonic *arg);
void *BitonicMergeMultiThreads(void *args);
void *BitonicSortMultiThreads(void *args);
void bitonicsort(int *array, int size, int threads);

#endif