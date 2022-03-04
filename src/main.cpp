#include <iostream>
#include "Timer.h"
#include "SortAlgorithm.h"
#include "Random.h"
#include <iterator>
#include <fstream>

using std::cout; 
using std::endl;

static const vector<int> TEST_SIZES{10, 50, 100, 200, 500, 1000, 2000, 5000, 7000, 10000,
                                    20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000}; 

int main() {
    auto test = GenerateSequenceOfSize<int>(1000);
    QuickSort(test);
    cout << std::is_sorted(test.begin(), test.end()) << endl;

    std::fstream stream("../res/result.csv");
    if (!stream.is_open())
        return -1;

    for (auto size: TEST_SIZES) {
        auto test_array = GenerateSequenceOfSize<int>(size);
        Timer timer;
        auto InsertionTime = timer.SortingTiming<int>(InsertionSort<int>, test_array);
        auto MergeSortTime = timer.SortingTiming<int>(MergeSort<int>, test_array);
        auto QuickSortTime = timer.SortingTiming<int>(QuickSort<int>, test_array);

        cout << size << "," << InsertionTime << "ms," << MergeSortTime << "ms," << QuickSortTime << "ms" << endl;
        stream << size << "," << InsertionTime << "ms," << MergeSortTime << "ms," << QuickSortTime << "ms" << endl;
    }
    return 0;
}