#ifndef _TIMER_H
#define _TIMER_H

#include <chrono>

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
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimePoint;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_EndTimePoint;
};

#endif