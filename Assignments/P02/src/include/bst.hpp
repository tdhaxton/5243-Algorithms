#pragma once

#include "dataStructure.hpp"

class Bst : public DataStructure{
protected:
    struct Node {
        int data;
        Node *left;
        Node *right;
        int height;

        explicit Node(int value)
            : data(value), left(nullptr), right(nullptr) {}
    };

    Node *root;

    // Recursive insert helper
    bool insert(Node *&node, int value) {
        c.comparisons++;
        if (!node) {
            node = new Node(value);
            c.inserts++;
            c.structural_ops++;
            return true;
        }

        c.comparisons++;
        if (value < node->data) {
            return insert(node->left, value);
        }
        c.comparisons++;
        if (value > node->data) {
            return insert(node->right, value);
        }

        // duplicate value: do nothing
        return false;
    }

    // Recursive search helper
    bool contains(Node *node, int value) const {
        c.comparisons++;
        if (!node) {
            return false;
        }

        c.comparisons++;
        if (value == node->data) {
            return true;
        }
        c.comparisons++;
        if (value < node->data) {
            return contains(node->left, value);
        }

        return contains(node->right, value);
    }

    // Find smallest node in subtree
    Node *findMin(Node *node) const {
        c.lookups++;
        while (node && node->left) {
            c.comparisons++;
            node = node->left;
        }
        // Incremented comparison here, because one comparison was made that
        // did not enter the loop.
        c.comparisons++;
        return node;
    }

    // Recursive erase helper
    bool erase(Node *&node, int value) {
        c.comparisons++;
        if (!node) {
            return false;
        }

        c.comparisons++;
        if (value < node->data) {
            return erase(node->left, value);
        }
        c.comparisons++;
        if (value > node->data) {
            return erase(node->right, value);
        }

        // Found node to delete

        // Case 1: leaf node
        if (!node->left && !node->right) {
            delete node;
            node = nullptr;
            c.deletes++;
            c.structural_ops++;
            return true;
        }

        // Case 2: only right child
        if (!node->left) {
            Node *temp = node;
            node = node->right;
            c.structural_ops++;
            delete temp;
            return true;
        }

        // Case 3: only left child
        if (!node->right) {
            Node *temp = node;
            node = node->left;
            c.structural_ops++;
            delete temp;
            return true;
        }

        // Case 4: two children
        Node *successor = findMin(node->right);
        node->data = successor->data;
        return erase(node->right, successor->data);
    }

    // Postorder cleanup helper
    void clear(Node *node) {
        if (!node) {
            return;
        }

        clear(node->left);
        clear(node->right);
        delete node;
    }

    // void _treeStructure(Node* root) {
    //     if(!root) {
    //         return;
    //     }

    //     else {
    //         std::cout << root;
    //         _treeStructure(root->left);
    //         _treeStructure(root->right);
    //     }
    // }

public:
    Bst() : root(nullptr) {}

    ~Bst() {
        clear(root);
        root = nullptr;
    }

    void reset() override {
        clear(root);
        root = nullptr;
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

    // void runJobFile(std::string fname) {
    //     std::ifstream f(fname);

    //     if (!f) {
    //         std::cerr << "Error: couldd not open file " << fname << '\n';
    //         return;
    //     }

    //     json j = json::parse(f);

    //     for (auto& element : j) {
    //         std::string op = element["op"];
    //         long long value = element["value"];

    //         if (op == "insert") {
    //             insert(value);
    //         }
    //         else if (op =="contains") {
    //             contains(value);
    //         }
    //         else if (op == "delete") {
    //             erase(value);
    //         }
    //         else {
    //             std::cerr << "Unknown operation: " << op << '\n';
    //         }
    //     }
    //     // iterate over json object and print out each operation with value
    //     // replace the print with actual operations, to process entire file.
    //     // for (auto &element : j){
    //     //     std::cout << element << '\n';
    //     // }
    // }

    bool insert(int value) override {
        return insert(root, value);
    }

    bool contains(int value) const override {
        c.lookups++;
        return contains(root, value);
    }

    bool erase(int value) override {
        return erase(root, value);
    }

    virtual const char *name() const {
        return "BST";
    }

    // void treeStructure() {
    //     return _treeStructure(root);
    // }
};