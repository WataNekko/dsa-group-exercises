#include "Random.h"

void GenerateRandomArray(int arr[], int size)
{
    srand(time(NULL));

    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % size;
    }
}
