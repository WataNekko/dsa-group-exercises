#ifndef RANDOM_H 
#define RANDOM_H

#include <random>
#include <vector>
#include <algorithm>
#include <type_traits>

template <typename T>
using uniform_distribution = 
typename std::conditional<
    std::is_floating_point<T>::value,
    std::uniform_real_distribution<T>,
    typename std::conditional<
        std::is_integral<T>::value,
        std::uniform_int_distribution<T>,
        void
    >::type
>::type;

template <typename T>
class RandomNumberBetween
{
public:
    RandomNumberBetween(T low, T high);
    int operator()();
private:
    std::mt19937 random_engine_;
    uniform_distribution<T> distribution_;
};

template <typename T>
std::vector<T> GenerateSequenceOfSize(size_t  n);

#include "Random.cpp"

#endif