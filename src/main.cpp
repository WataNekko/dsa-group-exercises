#include <iostream>
#include "Timer.h"

using std::cout; 
using std::endl;

int main() {
    Timer timer;
    timer.start();
    for(int i = 0; i < 100; ++i) {
        cout << "Hello World!" << endl;
    }
    timer.stop();
    cout << timer.elapsed() << endl;

    return 0;
}