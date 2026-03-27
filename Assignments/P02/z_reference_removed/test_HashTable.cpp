#include "hashTable.hpp"

int main(int argc, char** argv) {
    HashTable ht(17);
    std::string filename;
    std::ofstream outFile(filename);

    if (argc < 2) {
        std::cout << "Error: You need input and output filenames!" << std::endl;
        std::cout << "Usage: " <<
        "./test_HashTable ../workloads/workload_category_qty.json ../work_files/ds_wlCategory_qty.json"
        << std::endl;
    }

    ht.runJobFile(argv[1]);

    filename = argv[2];

    ht.save(filename, true);

    // ht.insert(10);
    // ht.insert(20);
    // ht.insert(30);
    // ht.insert(27);

    // std::cout << std::boolalpha;
    // std::cout << "contains 20: " << ht.contains(20) << "\n";
    // std::cout << "contains 99: " << ht.contains(99) << "\n";

    // ht.erase(20);

    // std::cout << "contains 20: " << ht.contains(20) << "\n";
}