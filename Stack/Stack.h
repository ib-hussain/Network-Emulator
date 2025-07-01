#ifndef STACK_H
#define STACK_H
// perfected -------------------------------------------------
#include "../BaseLibrariesFile.h"
#include "../LinkedList/NodeLL.h"

template <typename T2 = int>
struct Stack {
private:
    NodeLL<T2>* topNode;
    int elements;

    static NodeLL<T2> NULL_NODE;
    static T2 NULL_DATA;

public:
    Stack() : topNode(NULLpointer), elements(NULLint) {}

    Stack(const Stack& copyfrom) : topNode(NULLpointer), elements(0) {
        if (!copyfrom.topNode) return;
        // Copy elements in reverse order to preserve stack order
        Stack<T2> temp;
        NodeLL<T2>* curr = copyfrom.topNode;
        while (curr) {
            temp.push(curr->data);
            curr = curr->next;
        }
        while (!temp.isEmpty()) {
            push(temp.top());
            temp.pop();
        }
    }

    ~Stack() {
        while (!isEmpty()) pop();
    }

    bool push(const T2& value) {
        NodeLL<T2>* newNode = new NodeLL<T2>(value);
        newNode->next = topNode;
        if (topNode) topNode->prev = newNode;
        newNode->prev = NULLpointer;
        topNode = newNode;
        elements++;
        return true;
    }

    bool pop() {
        if (!topNode) return false;
        NodeLL<T2>* toDelete = topNode;
        topNode = topNode->next;
        if (topNode) topNode->prev = NULLpointer;
        delete toDelete;
        elements--;
        return true;
    }

    T2& top() {
        return topNode ? topNode->data : NULL_DATA;
    }

    const T2& top() const {
        return topNode ? topNode->data : NULL_DATA;
    }

    NodeLL<T2>& topNodeRef() {
        return topNode ? *topNode : NULL_NODE;
    }

    NodeLL<T2>* topNodePtr() {
        return topNode ? topNode : &NULL_NODE;
    }

    bool isEmpty() const {
        return elements == 0;
    }

    int size() const {
        return elements;
    }
};

// Static members
template <typename T2>
NodeLL<T2> Stack<T2>::NULL_NODE = NodeLL<T2>(T2());

template <typename T2>
T2 Stack<T2>::NULL_DATA = T2();

#endif // STACK_H
