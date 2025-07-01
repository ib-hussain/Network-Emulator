#ifndef DOUBLYCIRCULARLINKEDLIST_H
#define DOUBLYCIRCULARLINKEDLIST_H

#include "BaseLibrariesFile.h"
#include "NodeLL.h"
template <typename T2 = int>
struct DCLL {
private:
    NodeLL<T2>* tail;
    int nodes;
    // Static fallbacks
    static NodeLL<T2> NULL_NODE;
    static T2 NULL_DATA;
    NodeLL<T2>* getNodeAt(int index) const {
        if (index < 0 || index >= nodes || !tail)
            return &NULL_NODE;
        NodeLL<T2>* temp = tail->next;
        for (int i = 0; i < index; i++) temp = temp->next;
        return temp;
    }
public:
    DCLL() : tail(NULLpointer), nodes(NULLint) {}
    DCLL(const DCLL& copyfrom) : tail(NULLpointer), nodes(NULLint) {
        if (copyfrom.tail == NULLpointer) return;
        NodeLL<T2>* curr = copyfrom.tail->next;
        for (int i = 0; i < copyfrom.nodes; i++) {
            insert(curr->data);
            curr = curr->next;
        }
    }
    ~DCLL() {
        while (nodes > 0) remove();
    }
    bool insert(const T2& value) {
        NodeLL<T2>* newNode = new NodeLL<T2>(value);
        if (!tail) {
            newNode->next = newNode->prev = newNode;
            tail = newNode;
        } else {
            NodeLL<T2>* head = tail->next;
            newNode->next = head;
            newNode->prev = tail;
            head->prev = newNode;
            tail->next = newNode;
        }
        nodes++;
        return true;
    }
    bool remove() {
        if (!tail ) return false;
        NodeLL<T2>* toDelete = tail;
        if (tail->next == tail) {
            tail = NULLpointer;
        } else {
            toDelete->prev->next = toDelete->next;
            toDelete->next->prev = toDelete->prev;
            tail = toDelete->prev;
        }
        delete toDelete;
        nodes--;
        return true;
    }
    // Overloaded access operators
    T2& operator[](int index) {
        return getNodeAt(index)->data;
    }
    NodeLL<T2>& operator[](int index) {
        return *getNodeAt(index);
    }
    NodeLL<T2>* operator[](int index) {
        return getNodeAt(index);
    } 
    int size() const {
        return nodes;
    }
};
// Initialize static members
template <typename T2>
NodeLL<T2> DCLL<T2>::NULL_NODE = NodeLL<T2>(T2());
template <typename T2>
T2 DCLL<T2>::NULL_DATA = T2();
#endif // DOUBLYCIRCULARLINKEDLIST_H