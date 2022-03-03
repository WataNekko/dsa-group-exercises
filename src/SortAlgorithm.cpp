#ifndef _SORT_ALGORITHM_CPP
#define _SORT_ALGORITHM_CPP
#include "SortAlgorithm.h"
#include <algorithm>

using std::swap;

template<typename T>
void InsertionSort(vector<T>& data) {
    // The length of the vector
    size_t length = data.size();

    // Insertion Sort
    for (size_t i = 1; i < length; ++i) {
        auto key = data[i];

        size_t j = i - 1;
        // Insert data[j] into the sorted sequence data[1..j-1]
        for (; j >= 0 && data[j] > key; --j) {
            data[j + 1] = data[j];
        }
        data[j + 1] = key;
    }
} 

/**
 * @brief Return a new vector containing elements from a sub-range of this vector
 * 
 */
template<typename T>
vector<T> subList(const vector<T>& data, size_t start, size_t length) {
    size_t end = start + length - 1;
    vector<T> result;
    for (size_t i = start; i <= end; ++i) {
        result.push_back(data[i]);
    }

    return result;
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param data 
 */
template<typename T>
vector<T> subList(const vector<T>& data, size_t start) {
    size_t end = data.size() - 1;
    vector<T> result;
    for (size_t i = start; i <= end; ++i) {
        result.push_back(data[i]);
    }
    return result;
}

template<typename T>
void MergeSort(vector<T>& data) {
    if (data.size() <= 1) return;

    auto left = subList(data, 0, data.size() / 2);
    auto right = subList(data, data.size() / 2);

    MergeSort(left);
    MergeSort(right);

    size_t i1 = 0;
    size_t i2 = 0;

    for (size_t i = 0; i < data.size(); ++i) {
        if (i2 >= right.size() ||
            (i1 < left.size() && left[i1] < right[i2])) {
                data[i] = left[i1];
                ++i1;
            }
        else {
            data[i] = right[i2];
            ++i2;
        }
    }
}

template<typename T>
void QuickSort(vector<T>& data, int low, int high) {
    if (high - low >= 2) {
        T p = MedianOfThree(data, low, high);
        auto [left, right] = partition(data, p, low, high);
        QuickSort(data, low, left - 1);
        QuickSort(data, right + 1, high);
    }   
}

template<typename T>
void QuickSort(vector<T>& data) {
    QuickSort(data, 0, data.size() - 1);
}

template<typename T>
T MedianOfThree(vector<T>& data, int low, int high) {
    int mid = (low + high) / 2;
    if (data[mid] < data[low])
        swap(data[mid], data[low]);
    if (data[high] < data[low])
        swap(data[high], data[low]);
    if (data[mid] < data[high])
        swap(data[mid], data[high]);
    return data[high];
}

template<typename T>
std::pair<int, int> partition(vector<T>& data, T p, int low, int high) {
    int start = 0, end = high - 1;

    for (int i = 0; i <= end;) {
        if (data[i] < p)
            swap(data[i++], data[start++]);
        else if (data[i] > p)
            swap(data[i], data[end--]);
        else 
            ++i;
    }

    return {start, end};
}


#endif