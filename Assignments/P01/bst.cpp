#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int x) {
        data = x;
        left = right = nullptr;
    }
};

class GraphvizBST {
public:
    static void saveDotFile(const std::string &filename, const std::string &dotContent) {
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << dotContent;
            outFile.close();
            std::cout << "DOT file saved: " << filename << std::endl;
        } else {
            std::cerr << "Error: Could not open file " << filename << std::endl;
        }
    }

    static std::string generateDot(const Node *root) {
        std::string dot = "digraph BST {\n";
        dot += "    node [fontname=\"Arial\"];\n";
        dot += generateDotHelper(root);
        dot += "}\n";
        return dot;
    }

private:
    static std::string generateDotHelper(const Node *node) {
        if (!node)
            return "";
        std::string result;
        if (node->left) {
            result += "    " + std::to_string(node->data) + " -> " + std::to_string(node->left->data) + " [label=\"L\"];\n";
            result += generateDotHelper(node->left);
        } else {
            std::string nullNode = "nullL" + std::to_string(node->data);
            result += "    " + nullNode + " [shape=point];\n";
            result += "    " + std::to_string(node->data) + " -> " + nullNode + " [label=\"L\"];\n";
        }
        if (node->right) {
            result += "    " + std::to_string(node->data) + " -> " + std::to_string(node->right->data) + " [label=\"R\"];\n";
            result += generateDotHelper(node->right);
        } else {
            std::string nullNode = "nullR" + std::to_string(node->data);
            result += "    " + nullNode + " [shape=point];\n";
            result += "    " + std::to_string(node->data) + " -> " + nullNode + " [label=\"R\"];\n";
        }
        return result;
    }
};

class Bst {
    Node *root;

    void _print(Node *subroot) {
        if (!subroot) {
            return;
        } else {
            _print(subroot->left);
            cout << subroot->data << " ";
            _print(subroot->right);
        }
    }
    void _insert(Node *&subroot, int x) {
        if (!subroot) { // if(root == nullptr)
            subroot = new Node(x);
        } else {
            if (x < subroot->data) {
                _insert(subroot->left, x);
            } else {
                _insert(subroot->right, x);
            }
        }
    }
    bool _search(Node *&subroot, int x) {
        if (!subroot) {
            return false;
        }
        if (subroot->data == x) {
            return true;
        }
        if (x> subroot->data) {
            return _search(subroot->right, x);
        } else {
            return _search(subroot->left, x);
        }
    }
    Node* _getSuccessor(Node *curr){
        curr = curr->right;
        while (curr && curr->left) {
            curr = curr->left;
        }
        return curr;
    }
    void _bstDelete(Node *&subroot, int x) {
        if (!subroot) {
            return;
        }
        if (subroot->data > x) {
            _bstDelete(subroot->left, x);
        }
        else if (subroot->data < x) {
            _bstDelete(subroot->right, x);
        }
        else {
            if (!subroot->left) {
                Node* temp = subroot->right;
                delete subroot;
                subroot = temp;
                return;
            }
            if (!subroot->right) {
                Node* temp = subroot->left;
                delete subroot;
                subroot = temp;
                return;
            }
            
            Node* succ = _getSuccessor(subroot);
            subroot->data = succ->data;
            _bstDelete(subroot->right, succ->data);
        }
    }
    int _ipl(Node *root, int depth = 0) {
        if (!root)
            return 0; // Base case: Empty subtree contributes 0 to IPL
        return depth + _ipl(root->left, depth + 1) + _ipl(root->right, depth + 1);
    }

public:
    Bst() { root = nullptr; }
    void insert(int x) { _insert(root, x); }
    bool search(int key) { return _search(root, key); }
    void print() { _print(root); }
    void bstDelete(int x) { _bstDelete(root, x); }
    void saveDotFile(const std::string &filename) {
        std::string dotContent = GraphvizBST::generateDot(root);
        GraphvizBST::saveDotFile(filename, dotContent);
    }

    /**
     * Computes the Internal Path Length (IPL) of a Binary Search Tree (BST).
     *
     * Definition:
     * The Internal Path Length (IPL) of a BST is the sum of the depths of all nodes in the tree.
     * The depth of a node is the number of edges from the root to that node.
     *
     * Example:
     *        10
     *       /  \
     *      5    15
     *     / \     \
     *    2   7    20
     *
     * IPL = (depth of 10) + (depth of 5) + (depth of 15) + (depth of 2) + (depth of 7) + (depth of 20)
     *     = 0 + 1 + 1 + 2 + 2 + 2 = 8
     *
     * @param root Pointer to the root node of the BST.
     * @param depth Current depth of the node (default is 0 for the root call).
     * @return The sum of depths of all nodes (Internal Path Length).
     */
    int ipl() {
        return _ipl(root);
    }
};

bool unique_value(int *arr, int n, int x) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == x) {
            return false;
        }
    }
    return true;
}

int main() {
    Bst tree;

    // Empty tree
    tree.print();
    cout << tree.search(10);
    cout << tree.ipl();

    // Random unique values
    int root = pow(2, 15) / 2;
    int max = pow(2, 15) - 1;
    vector<int> arr;
    arr.push_back(root);
    tree.insert(root);
    for (int i = 1; i < 5000; i++) {
        int r = rand() % max;
        while (!unique_value(arr.data(), arr.size(), r)) {
            r = rand() % max;
        }
        tree.insert(r);
        arr.push_back(r);
    }

    tree.print();
    tree.saveDotFile("bst_snapshot.dot");

    // Balanced tree
    Bst tree2;
    tree2.insert(10);
    tree2.insert(5);
    tree2.insert(15);
    tree2.insert(2);
    tree2.insert(7);
    tree2.insert(20);
    tree2.insert(6);
    tree2.insert(27);
    tree2.insert(12);
    cout << "Internal Path Length: " << tree2.ipl() << endl;
    tree2.saveDotFile("bst_snapshot0.dot");

    tree2.bstDelete(25);
    tree2.print();
    tree2.saveDotFile("bst_snapshot0-1.dot");

    tree2.bstDelete(5);
    tree2.print();
    tree2.saveDotFile("bst_snapshot0-2.dot");

    tree2.bstDelete(10);
    tree2.print();
    tree2.saveDotFile("bst_snapshot0-3.dot");

    Bst t;

    // Single-node tree
    t.insert(11);
    t.print();
    cout << "Internal Path Length: " << t.ipl() << endl;
    t.saveDotFile("bst_snapshot1.dot");

    // Delete test
    t.bstDelete(11);
    t.print();
    t.saveDotFile("bst_snapshot.dot1-1");

    // Strictly increasing input for worst-case imbalance
    for (int i = 1; i <=10; i++)
        t.insert(i);

    t.print();
    t.saveDotFile("bst_snapshot2.dot");

    // Delete leaf with right child
    t.bstDelete(5);
    t.print();
    t.saveDotFile("bst_snapshot2-1.dot");

    // Delete leaf with no children
    t.bstDelete(10);
    t.print();
    t.saveDotFile("bst_snapshot.dot2-2");

    // Delete t
    t.bstDelete(9);
    t.bstDelete(8);
    t.bstDelete(7);
    t.bstDelete(6);
    t.bstDelete(4);
    t.bstDelete(3);
    t.bstDelete(2);
    t.bstDelete(1);

    // Strictly decreasing input for left imbalance
    for (int i = 10; i >=1; i--)
        t.insert(i);

    t.print();
    t.saveDotFile("bst_snapshot3.dot");

    for (int i = 10; i >= 1; i--)
        t.bstDelete(i);

    // Duplicate-heavy input
    int values[] = {10, 5, 10, 10, 5, 15, 15};
    for (int x : values)
        t.insert(x);

    t.print();
    t.saveDotFile("bst_snapshot4.dot");

    // Delete root with duplicates/two children
    t.bstDelete(10);
    t.print();
    t.saveDotFile("bst_snapshot4-1.dot");

    // Delete remaining tree
    for (int x : values) {
        t.bstDelete(x);
        t.print();
    }
    t.saveDotFile("bst_snapshot4-2.dot");
}
