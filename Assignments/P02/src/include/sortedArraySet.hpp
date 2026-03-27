#pragma once

#include "dataStructure.hpp"
#include <cstddef>

class SortedArraySet : public DataStructure {
private:
    int *data;
    std::size_t count;
    std::size_t capacity;
    std::size_t initialCapacity;

    void resize(std::size_t newCapacity) {
        int *newData = new int[newCapacity];

        for (std::size_t i = 0; i < count; i++) {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        capacity = newCapacity;

        c.resize_events++;

    }

    // Returns the index where value is found,
    // or where it should be inserted to maintain sorted order.
    std::size_t lowerBound(int value) const {
        std::size_t left = 0;
        std::size_t right = count;

        while (left < right) {
            c.comparisons++;
            std::size_t mid = left + (right - left) / 2;

            c.comparisons++;

            if (data[mid] < value) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        c.comparisons++;
        return left;
    }

    void clear() {
        delete[] data;
        data = new int[initialCapacity];
        capacity = initialCapacity;
        count = 0;
    }

public:
    explicit SortedArraySet(std::size_t initialCapacity = 8)
        : data(new int[initialCapacity]), count(0), capacity(initialCapacity), initialCapacity(initialCapacity) {}

    ~SortedArraySet() {
        delete[] data;
    }

    std::size_t size() const {
        return count;
    }

    bool empty() const {
        return count == 0;
    }

    void reset() override {
        clear();
    }

    bool contains(int value) const override {
        if (count == 0) {
            return false;
        }

        std::size_t pos = lowerBound(value);

        c.lookups++;

        return pos < count && data[pos] == value;
    }

    bool insert(int value) override {
        std::size_t pos = lowerBound(value);

        // Duplicate guard: do not insert if already present
        if (pos < count && data[pos] == value) {
            return false;
        }

        // Grow array if full
        if (count == capacity) {
            resize(capacity * 2);
        }

        // Shift elements right to make room
        for (std::size_t i = count; i > pos; i--) {
            data[i] = data[i - 1];
            c.structural_ops++;
        }

        data[pos] = value;
        count++;
        c.inserts++;

        return true;
    }

    bool erase(int value) override {
        if (count == 0) {
            return false;
        }

        std::size_t pos = lowerBound(value);

        if (pos >= count || data[pos] != value) {
            return false;
        }

        // Eager delete:
        // shift everything left immediately to close the gap
        for (std::size_t i = pos; i + 1 < count; i++) {
            data[i] = data[i + 1];
            c.structural_ops++;
        }

        count--;

        c.deletes++;

        return true;
    }

    void print() const {
        std::cout << "[";
        for (std::size_t i = 0; i < count; i++) {
            std::cout << data[i];
            if (i + 1 < count) {
                std::cout << ", ";
            }
        }
        std::cout << "]\n";
    }
};