#include <gtest/gtest.h>

extern "C" {
    #include <bitonic.h>
    #include <utils.h>
}

TEST(lab3, bitonic_sort) {
        std::vector<std::vector<int>> input;
        input = {
            {1,2},
            {2,1},
            {5,4,3,2},
            {1,2,3,4},
            {8,7,6,1,2,3,5,4},
            {6,4,9,10,5,1},
            {0,0,0,0,0,-1},
            {5,4,2,1,6,10}
        };
        std::vector<std::vector<int>> expectedOutput;
        expectedOutput = {
            {1,2},
            {1,2},
            {2,3,4,5},
            {1,2,3,4},
            {1,2,3,4,5,6,7,8},
            {1,4,5,6,9,10},
            {-1,0,0,0,0,0},
            {1,2,4,5,6,10}
        };
        for (size_t i = 0; i<input.size(); i++) {
            int *temp = (int *)malloc(sizeof(int) * input[i].size());
            int size = input[i].size();
            int newSize = 0;
            int *newArray = NULL;
            normalizeArray(&newArray, size, &newSize);
            for (int k = 0; k < size; k++) {
                newArray[k] = input[i][k];
            }
            bitonicsort(newArray, newSize, 4);
            for (size_t j = 0; j < expectedOutput[i].size(); j++) {
                EXPECT_EQ(newArray[j], expectedOutput[i][j]);
            }
            free(temp);
            free(newArray);
        }
}