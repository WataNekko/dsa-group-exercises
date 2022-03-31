#pragma once

#include <string>
#include <vector>

#include "linked_list.hpp"

namespace dsa {

    template <typename T>
    class HashTable {
    private:
        constexpr size_t SIZE = 100;
        std::vector<LinkedList<T>> buckets;

        size_t hash(const char *cstr)
        {
            return 0;
        }

    public:
        HashTable() : buckets(SIZE) {}

        T &operator[](const char *cstr)
        {
            return;
        }
    };

} // namespace dsa
