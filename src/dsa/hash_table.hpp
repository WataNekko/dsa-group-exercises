#pragma once

#include <stdexcept>
#include <string>
#include <vector>

#include "hash.hpp"
#include "linked_list.hpp"

namespace dsa {

    template <typename T>
    struct KeyValuePair {
        const std::string key;
        T value;
    };

    template <typename T, size_t BucketCount = 100>
    class HashTable {
    public:
        using Entry = KeyValuePair<T>;

        HashTable() : buckets_(BucketCount) {}

        template <size_t Size>
        HashTable(Entry(&&entries)[Size]) : buckets_(BucketCount)
        {
            for (auto &entry : entries) {
                insert(std::move(entry));
            }
        }

    private:
        void insert(Entry &&entry)
        {
            auto &bucket = getBucket(entry.key);

            for (auto &e : bucket) {
                if (e.key == entry.key) {
                    // key already exists
                    e.value = std::move(entry.value);
                    return;
                }
            }

            // insert new entry
            bucket.insert(std::move(entry));
        }

        template <typename K>
        inline LinkedList<Entry> &getBucket(const K &key)
        {
            return buckets_[dsa::hash(key, BucketCount)];
        }

        template <typename K>
        inline const LinkedList<Entry> &getBucket(const K &key) const
        {
            return buckets_[dsa::hash(key, BucketCount)];
        }

    public:
        template <typename K>
        T &operator[](K &&key)
        {
            auto &bucket = getBucket(key);

            for (auto &entry : bucket) {
                // find entry with same key
                if (entry.key == key) {
                    return entry.value;
                }
            }

            // key not found. insert new entry
            auto &entry = bucket.insert(Entry{std::forward<K>(key), T()});
            return entry.value;
        }

        T &operator[](const char *const key)
        {
            auto &bucket = getBucket(key);

            for (auto &entry : bucket) {
                // find entry with same key
                if (entry.key == key) {
                    return entry.value;
                }
            }

            // key not found. insert new entry
            auto &entry = bucket.insert(Entry{key, T()});
            return entry.value;
        }

        template <typename K>
        const T &operator[](const K &key) const
        {
            auto &bucket = getBucket(key);

            for (auto &entry : bucket) {
                // find entry with same key
                if (entry.key == key) {
                    return entry.value;
                }
            }

            // key not found. throw exception
            throw std::out_of_range("Key not found");
        }

        const T &operator[](const char *const key) const
        {
            auto &bucket = getBucket(key);

            for (auto &entry : bucket) {
                // find entry with same key
                if (entry.key == key) {
                    return entry.value;
                }
            }

            // key not found. throw exception
            throw std::out_of_range("Key not found");
        }

        template <typename K>
        inline bool remove(const K &key)
        {
            return getBucket(key)
                .removeIf([&](const Entry &entry) { return entry.key == key; });
        }

        inline bool remove(const char *const key)
        {
            return getBucket(key)
                .removeIf([&](const Entry &entry) { return entry.key == key; });
        }

    private:
        std::vector<LinkedList<Entry>> buckets_;

    }; // class HashTable

} // namespace dsa
