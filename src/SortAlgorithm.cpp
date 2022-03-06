#ifndef SORT_ALGORITHM_CPP
#define SORT_ALGORITHM_CPP

#include "SortAlgorithm.h"

void InsertionSort(int arr[], int size) {
    for (int i = 1; i < size; ++i) {
        int key = arr[i];

        int j = i - 1;
        // Insert data[j] into the sorted sequence data[1..j-1]
        for (; j >= 0 && arr[j] > key; --j) {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = key;
    }
}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int a1 = m - l + 1;
    int a2 = r - m;
  
    int L[a1], R[a2];
    
    for (i = 0; i < a1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < a2; j++)
        R[j] = arr[m + 1 + j];
  
    i = 0; 
    j = 0; 
    k = l; 
    while (i < a1 && j < a2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
  

    while (i < a1) {
        arr[k] = L[i];
        i++;
        k++;
    }
  
    while (j < a2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
  
void MergeSort(int arr[], int l, int r)
{
    if (l < r) {
        
        int m = l + (r - l) / 2;
  
        MergeSort(arr, l, m);
        MergeSort(arr, m + 1, r);
  
        merge(arr, l, m, r);
    }
}

void MergeSort(int arr[], int size) {
    MergeSort(arr, 0, size - 1);
}

int compareMyType (const void * a, const void * b)
{
  if ( *(int*)a <  *(int*)b ) return -1;
  if ( *(int*)a == *(int*)b ) return 0;
    return 1;
}

void QuickSort(int arr[], int size) {
    qsort(arr, size, sizeof(int), compareMyType);
}

#endif