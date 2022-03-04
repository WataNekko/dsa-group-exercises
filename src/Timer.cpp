#ifndef TIMER_CPP
#define TIMER_CPP

#include "Timer.h"

Timer::Timer() {}

Timer::Timer(bool AutoStart) {
    if (AutoStart) {
        start();
    }
}

Timer::~Timer() {
    Timer::stop();
}

void Timer::start() {
    m_StartTimePoint = std::chrono::high_resolution_clock::now();
}

void Timer::stop() {
    m_EndTimePoint = std::chrono::high_resolution_clock::now();
}

double Timer::elapsed() {
    auto start = std::chrono::time_point_cast<milliseconds> (m_StartTimePoint).time_since_epoch().count();
    auto end =  std::chrono::time_point_cast<milliseconds> (m_EndTimePoint).time_since_epoch().count();

    auto duration = end - start;

    return static_cast<double> (duration); 
}

#endif