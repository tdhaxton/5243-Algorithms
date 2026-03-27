#include "dataStructure.hpp"
#include "bst.hpp"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char** argv) {
    Bst tree;
    std::string filename;
    std::ofstream outFile(filename);

    if (argc < 2) {
        std::cout << "Error: You need input and output filenames!" << std::endl;
        std::cout << "Usage: " <<
        "./test_Bst ../workloads/workload_category_qty.json ../work_files/ds_wlCategory_qty.json" 
        << std::endl;
    }

    tree.runJobFile(argv[1]);
    
    // std::cout << "Enter output filename: ";
    // std::cin >> filename;

    filename = argv[2];
    
    // for(int i = 0; i < 100; i++) {
    //     tree.insert(rand());
    //     if (i % 10 == 0) {
    //         std::cout << tree.getCounters();
    //     }
    // }

    // tree.reset();

    // for(int i = 0; i < 100; i++) {
    //     tree.insert(rand());
    //     if (i % 10 == 0) {
    //         std::cout << tree.getCounters();
    //     }
    // }

    // std::cout << tree.getCounters();

    tree.save(filename, true);



    // tree.insert(50);
    // tree.insert(30);
    // tree.insert(70);
    // tree.insert(20);
    // tree.insert(40);
    // tree.insert(60);
    // tree.insert(80);

    // std::cout << std::boolalpha;
    // std::cout << "contains 40: " << tree.contains(40) << "\n";
    // std::cout << "contains 99: " << tree.contains(99) << "\n";

    // tree.erase(20); // leaf
    // tree.erase(30); // one child
    // tree.erase(50); // two children

    // std::cout << "contains 50: " << tree.contains(50) << "\n";
}