#pragma once

#include <cmath>

namespace dsa {

    size_t hash(const char *const cstr, size_t n);

    template <class Container>
    size_t hash(const Container &ctn, size_t n)
    {
        size_t hash = 0, i = 0;
        for (const auto &el : ctn) {
            constexpr auto TYPE_SIZE = sizeof(el) * 0x100;

            hash = (hash + static_cast<size_t>(el * std::pow(TYPE_SIZE, i)) % n) % n;
            ++i;
        }
        return hash;
    }

} // namespace dsa
