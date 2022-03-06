#include <iostream>
#include "Timer.h"
#include "SortAlgorithm.h"
#include "Random.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <thread>

using std::vector;
using std::endl;

static const vector<int> TEST_SIZES{10, 50, 100, 200, 500, 1000, 2000, 5000, 7000, 10000,
                                    20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
                                    
int main(int argc, char* argv[]) {

    if (argc > 2) {
        std::cout << "Error! Program only accept one filename or no filename" << endl;
        return -1;
    }

    std::ofstream file;
    const char* filename = argv[1];

    if (argc > 1) 
        file.open(filename, std::ios_base::out | std::ios_base::trunc);

    std::ostream& stream = (argc == 2) ? file : std::cout;

    if (!stream.good()) {
        std::cout << "Error with stream! Can not run the program" << endl;
        return -1;
    }
    stream << "\"Size of input\",\"Insertion Sort\",\"Merge Sort\",\"Quicksort\"" << endl;

    for (auto size: TEST_SIZES) {
        int* TestArray = new int[size];
        Timer timer;

        GenerateRandomArray(TestArray, size);
        auto InsertionTime = timer.SortingTiming(InsertionSort, TestArray, size);
        stream << size << ',' << InsertionTime << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));


        GenerateRandomArray(TestArray, size);
        auto MergeTime = timer.SortingTiming(MergeSort, TestArray, size);
        stream << ',' << MergeTime << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        GenerateRandomArray(TestArray, size);
        auto QuickTime = timer.SortingTiming(QuickSort, TestArray, size);
        stream << ',' << QuickTime << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        delete TestArray;
    }

    //std::cout << "Done!" << endl;

    return 0;
}
