#ifndef NODELL_H
#define NODELL_H
// perfected -------------------------------------------------

#include "../BaseLibrariesFile.h"

template <typename T1 = int>
struct NodeLL {
    T1 data;
    NodeLL* prev;
    NodeLL* next;
    // Constructors
    NodeLL() {
        prev = NULLpointer;
        next = NULLpointer;
    }
    NodeLL(NodeLL* copyfrom): data(copyfrom ? copyfrom->data : T1()), prev(NULLpointer), next(NULLpointer) {} 
    NodeLL(NodeLL& copyfrom): data(copyfrom.data), prev(NULLpointer), next(NULLpointer) {}
    NodeLL(NodeLL copyfrom): data(copyfrom.data), prev(NULLpointer), next(NULLpointer) {}
    NodeLL(const NodeLL* copyfrom): data(copyfrom ? copyfrom->data : T1()), prev(NULLpointer), next(NULLpointer) {}
    NodeLL(const NodeLL& copyfrom): data(copyfrom.data), prev(NULLpointer), next(NULLpointer) {}
    NodeLL(const T1& copyfrom): data(copyfrom), prev(NULLpointer), next(NULLpointer) {}
    NodeLL(const T1* copyfrom): data(copyfrom ? *copyfrom : T1()), prev(NULLpointer), next(NULLpointer) {}
    NodeLL(T1& copyfrom): data(copyfrom), prev(NULLpointer), next(NULLpointer) {}
    NodeLL(T1 copyfrom): data(copyfrom), prev(NULLpointer), next(NULLpointer) {}
    NodeLL(T1* copyfrom): data(copyfrom ? *copyfrom : T1()), prev(NULLpointer), next(NULLpointer) {}
    // Assignment Operators
    NodeLL& operator=(const NodeLL& copyfrom) {
        if (this != &copyfrom) {
            data = copyfrom.data;
        }
        return *this;
    }
    NodeLL& operator=(const NodeLL* copyfrom) {
        if (copyfrom && this != copyfrom) {
            data = copyfrom->data;
        }
        return *this;
    }
    NodeLL& operator=(const T1& copyfrom) {
        data = copyfrom;
        return *this;
    }
    NodeLL& operator=(const T1* copyfrom) {
        if (copyfrom) {
            data = *copyfrom;
        }
        return *this;
    }
    // Equality Operators
    bool operator==(const NodeLL& other) const {
        return data == other.data;
    }
    bool operator!=(const NodeLL& other) const {
        return data != other.data;
    }
    // Stream Output (for debugging)
    friend ostream& operator<<(ostream& os, const NodeLL& node) {
        os << node.data<<endl;
        return os;
    }// Destructor
    ~NodeLL() {
        prev = NULLpointer;
        next = NULLpointer;
    }
};
#endif