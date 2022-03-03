#include <iostream>
#include "Timer.h"
#include "SortAlgorithm.h"

using std::cout; 
using std::endl;

int main() {
    vector<int> v{55, 1, 0, 2, 66, 2134234, -342, 31432, 99};
    QuickSort(v);
    for(auto i: v) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}