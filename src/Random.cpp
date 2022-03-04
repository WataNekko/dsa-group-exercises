#ifndef RANDOM_CPP
#define RANDOM_CPP

#include "Random.h"

template <typename T>
RandomNumberBetween<T>::RandomNumberBetween(T low, T high)
    : random_engine_{std::random_device{}()}
    , distribution_{low, high} {};

template <typename T>
int RandomNumberBetween<T>::operator()() {
    return distribution_(random_engine_);
}   

template <typename T>
std::vector<T> GenerateSequenceOfSize(size_t  n) {
    std::vector<T> result;
    std::generate_n(std::back_inserter(result), n, RandomNumberBetween<T>(1, n));
    return result;
}

#endif