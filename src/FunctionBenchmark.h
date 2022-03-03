#ifndef _FUNCTION_BENCHMARK_H
#define _FUNCTION_BENCHMARK_H

#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Timer.h"

#define GET_VARIABLE_NAME(Variable) (#Variable)

using std::string;

template <typename value_type>
class FunctionBenchmark {
public: 
    FunctionBenchmark() {};
    explicit FunctionBenchmark(const std::function<value_type>& callback, size_t size);
    explicit FunctionBenchmark(const std::function<value_type>& callback, string filename, size_t size);
    ~FunctionBenchmark();

    double Timing();
    void WritingToFile();
    void WritingToConsole();
private:
    std::ofstream output;
    std::function<value_type> callback;
    size_t size;
    double TimeElapsed;
};

#include "FunctionBenchmark.cpp"

#endif