#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "../BaseLibrariesFile.h"
#include "../Message.h"
// Priority Queue Node
template <class PQ_DT1 = Message>
struct PQ_Node {
    friend struct PQ<PQ_DT1>; // Grant PQ access to private 'next'
private:
    PQ_Node* next;
    PQ_DT1 data;
    // Constructors
    PQ_Node(PQ_Node<PQ_DT1>& copy, bool kill = false): data(copy.data), next(NULLpointer) {
        if (kill) copy.data.destructor();
    }
    PQ_Node(PQ_DT1& value): data(value), next(NULLpointer) {}
    PQ_Node(): data(PQ_DT1()), next(NULLpointer) {}
    PQ_Node(PQ_Node<PQ_DT1>& copy): data(copy.data), next(NULLpointer) {}
    PQ_Node(PQ_Node<PQ_DT1>* copy): data(copy ? copy->data : PQ_DT1()), next(NULLpointer) {}
    PQ_Node<PQ_DT1>& operator=(const PQ_Node<PQ_DT1>& op) {
        if (this != &op) data = op.data;
        return *this;
    }
    PQ_Node<PQ_DT1>& operator=(const PQ_Node<PQ_DT1>* op) {
        if (this != op) data = op->data;
        return *this;
    }
    short int getPriority() const {
        return data.priority;
    }
};
// Priority Queue
template <class PQ_DT2 = Message>
struct PQ {
public:
    PQ_Node<PQ_DT2>* head;
    int nodes;
    PQ() : head(NULLpointer), nodes(0) {}
    bool isEmpty() const { return head == NULLpointer; }
    void insertionMAXpriority(PQ_DT2& val) {
        PQ_Node<PQ_DT2>* NN = new PQ_Node<PQ_DT2>(val);
        if (head == NULLpointer || head->getPriority() < NN->getPriority()) {
            NN->next = head;
            head = NN;
        } else {
            PQ_Node<PQ_DT2>* temp = head;
            while (temp->next != NULLpointer && temp->next->getPriority() >= val.priority) {
                temp = temp->next;
            }
            NN->next = temp->next;
            temp->next = NN;
        }
        nodes++;
    }
    void deletionMAXpriority() {
        if (isEmpty()) {
            if (debug) cout << "Queue is empty" << endl;
            return;
        }
        PQ_Node<PQ_DT2>* temp = head;
        head = head->next;
        delete temp;
        nodes--;
    }
    PQ_DT2& peekMAXpriority() const {
        if (isEmpty()) {
            if (debug) cout << "Queue is empty" << endl;
            static PQ_DT2 nullVal;
            return nullVal;
        }
        if (debug) cout << "highest priority element is: " << head->data << endl;
        return head->data;
    }
    void displayMAXpriority() const {
        if (isEmpty()) {
            if (debug) cout << "Queue is empty" << endl;
            return;
        }
        if (debug) cout << "Max-Priority Queue: " << endl;
        PQ_Node<PQ_DT2>* temp = head;
        while (temp != NULLpointer) {
            if (debug) cout << temp->data << " (Priority: " << temp->getPriority() << ") -> ";
            temp = temp->next;
        }
        if (debug) cout << "NULL" << endl;
    }
    PQ_Node<PQ_DT2>& operator[](int key) const {
        PQ_Node<PQ_DT2>* temp = head;
        int count = 0;
        while (temp) {
            if (count == key) return *temp;
            temp = temp->next;
            count++;
        }
        static PQ_Node<PQ_DT2> nullNode(PQ_DT2());
        return nullNode;
    }
    ~PQ() {
        while (!isEmpty()) deletionMAXpriority();
    }
    bool Enqueue(PQ_DT2& val) {
        if (&val == NULLpointer) return false;
        insertionMAXpriority(val);
        return true;
    }
    PQ_DT2& Dequeue() {
        if (isEmpty()) {
            static PQ_DT2 nullVal;
            return nullVal;
        }
        PQ_DT2& highest = peekMAXpriority();
        deletionMAXpriority();
        return highest;
    }
};

#endif
