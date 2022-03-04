#ifndef TIMER_H
#define TIMER_H

#include <vector>
#include <chrono>
#include <functional>
class Timer 
{
public:
    using milliseconds = std::chrono::duration<double, std::milli>;
    Timer();
    explicit Timer(bool AutoStart);
    ~Timer();
    void start();
    void stop();
    double elapsed();
    template <typename T>
    double SortingTiming(std::function<void(std::vector<T>&)> SortFunc, std::vector<T> collection);
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimePoint;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_EndTimePoint;
};

template <typename T>
double Timer::SortingTiming(std::function<void(std::vector<T>&)> SortFunc, std::vector<T> collection) {
    start();
    SortFunc(collection);
    stop();
    return elapsed();
}

#endif