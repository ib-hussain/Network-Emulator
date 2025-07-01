#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H
// perfected -------------------------------------------------
#include "NodeLL.h"
//for the router's linear list and in general as well
template <typename T2 = int>
struct SLL {
private:
    NodeLL<T2>* head;
    int nodes;
    static NodeLL<T2> NULL_NODE;
    static T2 NULL_DATA;
    NodeLL<T2>* getNodeAt(int index) const {
        if (index < 0 || index >= nodes || !head)
            return &NULL_NODE;
        NodeLL<T2>* temp = head;
        for (int i = 0; i < index; i++)
            temp = temp->next;
        return temp;
    }
public:
    SLL() : head(NULLpointer), nodes(NULLint) {}
    SLL(const SLL& copyfrom) : head(NULLpointer), nodes(NULLint) {
        NodeLL<T2>* curr = copyfrom.head;
        for (int i = 0; i < copyfrom.nodes; i++) {
            insert(curr->data);
            curr = curr->next;
        }
    }
    ~SLL() {
        while (nodes > 0) remove();
    }
    bool insert(const T2& value) {
        NodeLL<T2>* newNode = new NodeLL<T2>(value);
        if (!head) {
            head = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        nodes++;
        return true;
    }
    bool remove() {
        if (!head) return false;
        NodeLL<T2>* toDelete = head;
        head = head->next;
        delete toDelete;
        nodes--;
        return true;
    }
    // Overloaded access
    T2& operator[](int index) {
        return getNodeAt(index)->data;
    }
    NodeLL<T2>& operator()(int index) {
        return *getNodeAt(index);
    }
    NodeLL<T2>* operator()(int index, bool) {
        return getNodeAt(index);
    }
    int size() const {
        return nodes;
    }
};
// Static members
template <typename T2>
NodeLL<T2> SLL<T2>::NULL_NODE = NodeLL<T2>(T2());
template <typename T2>
T2 SLL<T2>::NULL_DATA = T2();

#endif // SINGLYLINKEDLIST_H
