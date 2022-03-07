#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <functional>
#include <vector>
class Timer {
public:
    using milliseconds = std::chrono::duration<double, std::milli>;
    Timer();
    explicit Timer(bool AutoStart);
    ~Timer();
    void start();
    void stop();
    double elapsed();
    template <typename T>
    double SortingTiming(std::function<void(std::vector<T> &)> SortFunc, std::vector<T> collection);
    double SortingTiming(void (*SortFunc)(int *, int), int arr[], int size);
    double AverageSortingTiming(void (*SortFunc)(int *, int), int arr[], int size, int iterations = 10);

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimePoint;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_EndTimePoint;
};

template <typename T>
double Timer::SortingTiming(std::function<void(std::vector<T> &)> SortFunc, std::vector<T> collection)
{
    start();
    SortFunc(collection);
    stop();
    return elapsed();
}

#endif