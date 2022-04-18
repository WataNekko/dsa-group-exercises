#include "hash.hpp"

namespace dsa {

    size_t hash(const char *const cstr, size_t n)
    {
        size_t hash = 0;
        for (auto ptr = cstr; *ptr != '\0'; ++ptr) {
            constexpr auto TYPE_SIZE = sizeof(*ptr) * 0x100;

            hash = (hash + static_cast<size_t>(*ptr * std::pow(TYPE_SIZE, ptr - cstr)) % n) % n;
        }
        return hash;
    }

} // namespace dsa
