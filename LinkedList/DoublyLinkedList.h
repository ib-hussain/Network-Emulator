#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
// perfected -------------------------------------------------

#include "../BaseLibrariesFile.h"
#include "NodeLL.h"

template <typename T2 = int>
struct DLL {
private:
    NodeLL<T2>* head;
    NodeLL<T2>* tail;
    int nodes;
    static NodeLL<T2> NULL_NODE;
    static T2 NULL_DATA;
    NodeLL<T2>* getNodeAt(int index) const {
        if (index < 0 || index >= nodes || !head)
            return &NULL_NODE;
        NodeLL<T2>* temp = head;
        for (int i = 0; i < index; i++) temp = temp->next;
        return temp;
    }
public:
    DLL() : head(NULLpointer), tail(NULLpointer), nodes(NULLint) {}
    DLL(const DLL& copyfrom) : head(NULLpointer), tail(NULLpointer), nodes(NULLint) {
        if (!copyfrom.head) return;
        NodeLL<T2>* curr = copyfrom.head;
        for (int i = 0; i < copyfrom.nodes; i++) {
            insert(curr->data);
            curr = curr->next;
        }
    }
    ~DLL() {
        while (nodes > 0) remove();
    }
    bool insert(const T2& value) {
        NodeLL<T2>* newNode = new NodeLL<T2>(value);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        nodes++;
        return true;
    }
    bool remove() {
        if (!tail) return false;

        NodeLL<T2>* toDelete = tail;
        if (head == tail) {
            head = tail = NULLpointer;
        } else {
            tail = tail->prev;
            tail->next = NULLpointer;
        }
        delete toDelete;
        nodes--;
        return true;
    }
    // Overloaded access operators
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
// Initialize static members
template <typename T2>
NodeLL<T2> DLL<T2>::NULL_NODE = NodeLL<T2>(T2());
template <typename T2>
T2 DLL<T2>::NULL_DATA = T2();
#endif // DOUBLYLINKEDLIST_H