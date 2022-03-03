#ifndef _FUNCTION_BENCHMARK_CPP
#define _FUNCTION_BENCHMARK_CPP

#include "FunctionBenchmark.h"

template <typename value_type>
FunctionBenchmark<value_type>::FunctionBenchmark(const std::function<value_type>& callback, size_t size) :
    callback(callback), 
    size(size)
{
    string filename = GET_VARIABLE_NAME(callback) + ".csv";
    output.open(filename.c_str());
}

template <typename value_type>
FunctionBenchmark<value_type>::FunctionBenchmark(const std::function<value_type>& callback, string filename, size_t size) :
    callback(callback),
    size(size) 
{
    output.open(filename.c_str());
}

template <typename value_type>
FunctionBenchmark<value_type>::~FunctionBenchmark() {
    output.close();
}

template <typename value_type>
double FunctionBenchmark<value_type>::Timing() {
    Timer timer{true};
    callback;
    timer.stop():
    TimeElapsed = timer.elasped();
    return TimeElapsed;
}

template <typename value_type>
void FunctionBenchmark<value_type>::WritingToFile() {
    
}

#endif