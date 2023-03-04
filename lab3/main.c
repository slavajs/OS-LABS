#include "stdio.h"
#include "stdlib.h"
#include "bitonic.h"
#include <sys/time.h>
#include "utils.h"


int main(int argc, char *argv[]){
    int threads = 1;

    if(argc == 2){ // читаем количество потоков
        threads = atoi(argv[1]);
    }
    int input_size;
    scanf("%d",&input_size);

    int size_array;
    int *array = NULL;
    normalizeArray(&array, input_size, &size_array);
    for(int i = 0; i < input_size; ++i) {
        scanf("%d",array+i);
    }

    struct timeval startwtime, endwtime;
    gettimeofday(&startwtime, NULL);

    bitonicsort(array, size_array, threads);

    gettimeofday(&endwtime, NULL);
    double time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6 + endwtime.tv_sec - startwtime.tv_sec);
    printf("Time for executing: %f\n", time);

    printf("Sorted array:");
    for(int i=0;i<input_size;++i){
        printf("%d ",array[i]);
    }
    printf("\n");
    free(array);
    return 0;
}