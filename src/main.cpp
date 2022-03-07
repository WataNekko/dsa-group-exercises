#include "SortAlgorithm.h"
#include "Timer.h"
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

using std::endl;
using std::vector;

static const vector<int> TEST_SIZES{10, 50, 100, 200, 500, 1000, 2000, 5000, 7000, 10000,
                                    20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};

int main(int argc, char *argv[])
{

    if (argc > 2) {
        std::cout << "Error! Program only accept one filename or no filename" << endl;
        return -1;
    }

    std::ofstream file;
    const char *filename = argv[1];

    if (argc > 1)
        file.open(filename, std::ios_base::out | std::ios_base::trunc);

    std::ostream &stream = (argc == 2) ? file : std::cout;

    if (!stream.good()) {
        std::cout << "Error with stream! Can not run the program" << endl;
        return -1;
    }

    // Start benchmark
    std::cout << "[Running benchmark...]" << endl;

    stream << "\"Size of input\",\"Insertion Sort\",\"Merge Sort\",\"Quicksort\"" << endl;

    for (auto size : TEST_SIZES) {
        int *array = new int[size];
        Timer timer;

        double InsertionTime = timer.AverageSortingTiming(InsertionSort, array, size);
        stream << size << ',' << InsertionTime << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        double MergeTime = timer.AverageSortingTiming(MergeSort, array, size);
        stream << ',' << MergeTime << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        double QuickTime = timer.AverageSortingTiming(QuickSort, array, size);
        stream << ',' << QuickTime << endl;

        delete[] array;
    }

    std::cout << "\n[Done benchmark]" << endl;

    return 0;
}
