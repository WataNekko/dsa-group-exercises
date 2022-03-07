#include "Timer.h"
#include "Random.h"

Timer::Timer() {}

Timer::Timer(bool AutoStart)
{
    if (AutoStart) {
        start();
    }
}

Timer::~Timer()
{
    Timer::stop();
}

void Timer::start()
{
    m_StartTimePoint = std::chrono::high_resolution_clock::now();
}

void Timer::stop()
{
    m_EndTimePoint = std::chrono::high_resolution_clock::now();
}

double Timer::elapsed()
{
    auto start = std::chrono::time_point_cast<milliseconds>(m_StartTimePoint).time_since_epoch().count();
    auto end = std::chrono::time_point_cast<milliseconds>(m_EndTimePoint).time_since_epoch().count();

    auto duration = end - start;

    return static_cast<double>(duration);
}

double Timer::SortingTiming(void (*SortFunc)(int *, int), int arr[], int size)
{
    start();
    SortFunc(arr, size);
    stop();
    return elapsed();
}

double Timer::AverageSortingTiming(void (*SortFunc)(int *, int), int arr[], int size, int iterations)
{
    double sum = 0.0;
    for (int i = 0; i < iterations; ++i) {
        GenerateRandomArray(arr, size);
        sum += SortingTiming(SortFunc, arr, size);
    }
    return sum / iterations;
}