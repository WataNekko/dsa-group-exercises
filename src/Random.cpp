#ifndef RANDOM_CPP
#define RANDOM_CPP

#include "Random.h"

void GenerateRandomArray(int arr[], int size) {
    srand(time(NULL));

    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % size;
    }
}

#endif