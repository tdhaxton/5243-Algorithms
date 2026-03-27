// ! TODO: Fails at array (runs bst and hash); throws instance of std::bad_alloc

#include "dataStructure.hpp"
#include "bst.hpp"
#include "hashTable.hpp"
#include "linkedList.hpp"
#include "sortedArraySet.hpp"
#include <filesystem>

struct DSRunner {
    std::string name;
    DataStructure* ds;

    DSRunner(const std::string& n, DataStructure* d)
        : name(n), ds(d) {}
};

int main(int argc, char **argv) {
    Bst tree;
    HashTable ht(17);
    LinkedList list;
    SortedArraySet s;

    std::vector<DSRunner> runners = {
        {"bst", &tree},
        {"hash", &ht},
        {"array", &s},
        {"list", &list}
    };

    std::vector<char> cats = {'A', 'B', 'C', 'D'};
    std::vector<int> qtys = {1000, 5000, 10000, 20000};

    for (char cat : cats) {
        for (int qty : qtys) {
            std::string workload = "./workloads/workload_" + std::string(1, cat) + 
            "_" + std::to_string(qty) + ".json";

            for (auto& runner : runners) {
                runner.ds->reset();
                runner.ds->reset_counters();
                runner.ds->runJobFile(workload);
                
                std::string outFile = 
                    "../work_files/" + runner.name + "_" +
                    std::string(1, cat) + "_" +
                    std::to_string(qty) + ".json";
                
                runner.ds->save(outFile, true);

                std::cout << "Completed " << runner.name
                          << " on " << workload << "\n";
            }
        }
    }

    // std::string filename;
    // std::ofstream outFile(filename);

    // if (argc < 2) {
    //     std::cout << "Error: You need input and output filenames!" << std::endl;
    //     std::cout << "Usage: " <<
    //     "./test_ds ../workloads/workload_category_qty.json ../work_files/ds_wlCategory_qty.json"
    //     << std::endl;
    // }

    
}