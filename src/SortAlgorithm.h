#ifndef SORT_ALGORITHM_H
#define SORT_ALGORITHM_H

#include <vector>
#include <algorithm>

using std::swap;
using std::vector;

template<typename T>
void InsertionSort(vector<T>& data);

template<typename T>
void MergeSort(vector<T>& data);

template<typename T>
void QuickSort(vector<T>& data);

template<typename T>
T MedianOfThree(vector<T>& data,int low, int high);

template<typename T>
std::pair<int, int> partition(vector<T>& data, T p, int low, int high);

#include "SortAlgorithm.cpp"

#endif