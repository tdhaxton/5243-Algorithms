#include "dataStructure.hpp"

class LinkedList : public DataStructure {
private:
    struct Node {
        int data;
        Node *next;

        Node(int v) : data(v), next(nullptr) {}
    };

    Node *head;

    void clear() {
        Node* curr = head;

        while (curr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }

        head = nullptr;
    }

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        Node *curr = head;

        while (curr) {
            Node *temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    void reset() override {
        clear();
    }

    bool insert(int value) override {
        if (contains(value))
            return false;

        Node *n = new Node(value);

        n->next = head;
        head = n;

        c.inserts++;
        c.shifts_relinks++;

        return true;
    }

    bool contains(int value) const override {
        c.lookups++;
        Node *curr = head;

        while (curr) {
            c.comparisons++;
            if (curr->data == value) {
                return true;
            }

            curr = curr->next;
        }

        return false;
    }

    bool erase(int value) override {
        Node *curr = head;
        Node *prev = nullptr;

        while (curr) {
            c.comparisons++;
            if (curr->data == value) {

                if (prev)
                    prev->next = curr->next;
                else
                    head = curr->next;

                delete curr;
                c.deletes++;
                c.shifts_relinks++;
                return true;
            }

            prev = curr;
            curr = curr->next;
        }

        return false;
    }

    void print() const {
        Node *curr = head;

        while (curr) {
            std::cout << curr->data << " ";
            curr = curr->next;
        }

        std::cout << "\n";
    }
};