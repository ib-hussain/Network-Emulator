#ifndef SINGLYCIRCULARLINKEDLIST_H
#define SINGLYCIRCULARLINKEDLIST_H

#include "BaseLibrariesFile.h"
#include "NodeLL.h"
template <typename T2 = int>
struct SCLL {
private:
    NodeLL<T2>* tail; // Points to last node (tail->next is head)
    int nodes;
    static NodeLL<T2> NULL_NODE;
    static T2 NULL_DATA;
    NodeLL<T2>* getNodeAt(int index) const {
        if (index < 0 || index >= nodes || !tail)
            return &NULL_NODE;
        NodeLL<T2>* temp = tail->next; // head
        for (int i = 0; i < index; i++)
            temp = temp->next;
        return temp;
    }
public:
    SCLL() : tail(NULLpointer), nodes(NULLint) {}
    SCLL(const SCLL& copyfrom) : tail(NULLpointer), nodes(NULLint) {
        if (!copyfrom.tail) return;
        NodeLL<T2>* curr = copyfrom.tail->next; // Start at head
        for (int i = 0; i < copyfrom.nodes; i++) {
            insert(curr->data);
            curr = curr->next;
        }
    }
    ~SCLL() {
        while (nodes > 0) remove();
    }
    bool insert(const T2& value) {
        NodeLL<T2>* newNode = new NodeLL<T2>(value);
        if (!tail) {
            tail = newNode;
            tail->next = tail; // Self-loop
        } else {
            newNode->next = tail->next; // New node points to head
            tail->next = newNode;       // Tail points to new node
            tail = newNode;             // New node becomes tail
        }
        nodes++;
        return true;
    }
    bool remove() {
        if (!tail) return false;

        NodeLL<T2>* head = tail->next;
        if (tail == head) {
            delete tail;
            tail = NULLpointer;
        } else {
            NodeLL<T2>* temp = head;
            while (temp->next != tail) temp = temp->next; // Find prev to tail
            temp->next = tail->next; // Skip tail
            delete tail;
            tail = temp;
        }
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
NodeLL<T2> SCLL<T2>::NULL_NODE = NodeLL<T2>(T2());
template <typename T2>
T2 SCLL<T2>::NULL_DATA = T2();

#endif // CIRCULARSINGLYLINKEDLIST_H