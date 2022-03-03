#ifndef _SORT_ALGORITHM_H
#define _SORT_ALGORITHM_H

#include <vector>
#include <cstddef>
#include <iostream>
using std::cout; using std::endl;
using std::vector;

/**
 * @brief Given a vector of any type that can be compared, sort it using insertion sort.
 * 
 * @param toSort The vector of any type that are comparable. 
 * 
 * @return 
 */

template<typename T>
void InsertionSort(vector<T>& data);

/**
 * @brief 
 * 
 */

template<typename T>
void MergeSort(vector<T>& data);

/**
 * @file SortAlgorithm.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */

template<typename T>
void QuickSort(vector<T>& data);

/**
 * @file SortAlgorithm.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */

template<typename T>
T MedianOfThree(vector<T>& data,int low, int high);

/**
 * @file SortAlgorithm.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */

template<typename T>
std::pair<int, int> partition(vector<T>& data, T p, int low, int high);

#include "SortAlgorithm.cpp"

#endif