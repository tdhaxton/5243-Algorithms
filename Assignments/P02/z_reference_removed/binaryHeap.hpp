// This was part of 5243-Algorithms/Assignments/P02/src/include and wasn't included
// in the final project

#pragma once

#include <stdexcept>
#include <utility>
#include <vector>
#include "counters.hpp"

class BinaryHeap {
private:
    std::vector<int> data;
    Counters c;

    int parent(int i) const {
        return (i - 1) / 2;
    }

    int left(int i) const {
        return 2 * i + 1;
    }

    int right(int i) const {
        return 2 * i + 2;
    }

    void siftUp(int i) {
        while (i > 0 && data[i] < data[parent(i)]) {
            c.comparisons++;
            std::swap(data[i], data[parent(i)]);
            c.structural_ops++;
            i = parent(i);
        }
        c.comparisons++;
    }

    void siftDown(int i) {
        int n = static_cast<int>(data.size());

        while (true) {
            int l = left(i);
            int r = right(i);
            int smallest = i;

            c.comparisons++;
            if (l < n && data[l] < data[smallest]) {
                smallest = l;
            }

            c.comparisons++;
            if (r < n && data[r] < data[smallest]) {
                smallest = r;
            }

            c.comparisons++;
            if (smallest == i) {
                break;
            }

            std::swap(data[i], data[smallest]);
            c.structural_ops++;
            i = smallest;
        }
    }

public:
    BinaryHeap() = default;

    explicit BinaryHeap(const std::vector<int> &values) : data(values) {
        buildHeap();
    }

    void reset(){
        data.clear();
    }

    void reset_counters(){
        c = Counters{};
    }

    Counters counters(){
        return c;
    }

    bool empty() const {
        return data.empty();
    }

    std::size_t size() const {
        return data.size();
    }

    int top() const {
        if (data.empty()) {
            throw std::runtime_error("heap is empty");
        }
        return data[0];
    }

    void push(int value) {
        c.inserts++;
        data.push_back(value);
        c.structural_ops++;
        siftUp(static_cast<int>(data.size()) - 1);
    }

    bool pop() {
        c.deletes++;
        if (data.empty()) {
            return false;
        }

        if (data.size() == 1) {
            c.comparisons++;
            data.pop_back();
            c.structural_ops++;
            return true;
        }

        data[0] = data.back();
        data.pop_back();
        c.structural_ops++;
        siftDown(0);
        return true;
    }

    void buildHeap() {
        for (int i = static_cast<int>(data.size()) / 2 - 1; i >= 0; --i) {
            siftDown(i);
        }
    }
};