#pragma once

#include "counters.hpp"
#include "json.hpp"
#include <fstream>
#include <iostream>
#include <string>

class DataStructure {
protected:
    Counters c{};

public:
    virtual ~DataStructure() = default;

    virtual bool insert(int key) = 0;
    virtual bool contains(int key) const = 0;
    virtual bool erase(int key) = 0;
    virtual void reset() = 0;
        
    void reset_counters() {
        c = {};
    }

    void save(std::string filename, bool dict = true) {
        c.saveCounters(filename, dict);
    }
    
    Counters getCounters() const {
        return c;
    }

    void runJobFile(const std::string fname) {
        std::ifstream f(fname);

        if (!f) {
            std::cerr << "Error: could not open file " << fname << '\n';
            return;
        }

        json j = json::parse(f);

        for (auto& element : j) {
            std::string op = element["op"];
            long long value = element["value"];

            if (op == "insert") {
                insert(value);
            }
            else if (op == "contains") {
                contains(value);
            }
            else if (op == "delete") {
                erase(value);
            }
            else {
                std::cerr << "Unknown operation: " << op << '\n';
            }
        }
    }
};