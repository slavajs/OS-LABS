#include "utils.h"


void normalizeArray(int **newArray, int sizePrev, int *newSize) {
    int size_array = SizeStep(sizePrev); 
    int *array = malloc(sizeof(int)*size_array);
    for(int i = sizePrev; i < size_array; ++i) {
        array[i] = MAXINT;
    }
    *newSize = size_array;
    *newArray=  array;
}


int SizeStep(int Num){
    int i = 1;
    while(i < Num) {
        i *= 2;
    }
    return i;
}

// void outputArray(int *array, int size) {

// }