#pragma once

#include "dataStructure.hpp"
#include <cstddef>
#include <vector>
#include "counters.hpp"
#include "json.hpp"
#include <iostream>
#include <string>

class HashTable : public DataStructure {
private:
    std::vector<std::vector<int>> table;
    std::size_t capacity;

    // Integer hash function
    std::size_t hash(int key) const {
        return static_cast<std::size_t>(key) * 2654435761u;
    }

    // Compress hash value into a valid bucket index
    std::size_t indexFor(int key) const {
        return hash(key) % capacity;
    }

    void clear() {
        for (auto& bucket : table) {
            bucket.clear();
        }
    }

public:
    explicit HashTable(std::size_t cap = 101)
        : table(cap), capacity(cap) {}

    bool insert(int key) override {
        std::size_t idx = indexFor(key);
        auto &bucket = table[idx];

        // Ignore duplicates
        for (int value : bucket) {
            if (value == key) {
                return false;
            }
        }

        bucket.push_back(key);
        c.inserts++;
        c.structural_ops++;
        return true;
    }

    bool contains(int key) const override {
        c.lookups++;
        std::size_t idx = indexFor(key);
        const auto &bucket = table[idx];

        for (int value : bucket) {
            c.comparisons++;
            if (value == key) {
                return true;
            }
        }

        return false;
    }

    bool erase(int key) override {
        std::size_t idx = indexFor(key);
        auto &bucket = table[idx];

        for (std::size_t i = 0; i < bucket.size(); i++) {
            c.comparisons++;
            if (bucket[i] == key) {
                // swap-pop delete: fast, order not preserved
                bucket[i] = bucket.back();
                bucket.pop_back();
                c.structural_ops++;
                c.deletes++;
                return true;
            }
        }

        return false;
    }

    void reset() override {
        clear();
    }

    // void reset_counters() {
    //     c = {};
    // }

    // void save(std::string filename, bool dict = true) {
    //     c.saveCounters(filename, dict);
    // }

    // Counters getCounters() {
    //     return c;
    // }
};