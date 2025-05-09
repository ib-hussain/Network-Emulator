#ifndef QUEUE_H
#define QUEUE_H
#include "BaseLibrariesFile.h" // Ensure this file exists in the same directory or provide the correct path
#include <ctime> // Added for time functions

// Ensure this file exists in the same directory as Queue.h         // Include for ostream
// making a queue class that will be used in the graph class to hold the nodes that are being visited in the graph
// this is a circular linked list that will hold the nodes that are being visited in the graph
// using templates
// so that we can use any data type in the queue
// this is a singly linked list that will hold the nodes that are being visited in the graph

// class node()
//  static full int x -1  var node - id enhancer

// const int FULL_INT = -32767; // constant to hold the value of the full int
// this is a constant that will be used to check if the queue is empty or not

// Forward declaration of the Queue class template
template <typename T>
class Queue;

template <typename T = int>
struct Q_Node {
    T data;
    long long int ID;
    Q_Node* next;
    static long long int enhancer;

    Q_Node(T value) {
        this->data = value;
        this->next = nullptr;
        ID = 1 + enhancer;
        enhancer++;
    }

    ~Q_Node() {
        this->next = nullptr;
    }

    friend class Queue<T>;
};

template <typename T>
long long int Q_Node<T>::enhancer = -32767; // Assuming FULLint = -32767

//

template <typename T1 = int>
struct Queue {
    Q_Node<T1>* head;
    Q_Node<T1>* tail;
    int size;
    Queue() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    bool Enqueue(T1& value) {
        Q_Node<T1>* nn = new Q_Node<T1>(value);
        if (!head) {
            head = nn;
            tail = nn;
        } else {
            tail->next = nn;
            tail = nn;
        }
        size++;
        return true;
    }

    T1 Dequeue() {
        static T1 NullNode4;
        if (head == nullptr) return NullNode4;
        
        // Add latency before dequeuing
        clock_t start_time = clock();
        while ((clock() - start_time) < latency_queue_forwarding * CLOCKS_PER_SEC / 1000) // Convert milliseconds to clock ticks
        // while (latency_queue_forwarding > 0) // Uncomment this line if you want to use a busy wait
        {// wait
        }
        
        T1 value = head->data;
        Q_Node<T1>* temp = head;
        head = head->next;
        delete temp;
        size--;
        return value;
    }

    bool isEmpty() {
        return size == 0;
    }

    friend ostream& operator<<(ostream& os, const Queue<T1>& queue) {
        Q_Node<T1>* current = queue.head;
        while (current != nullptr) {
            os << current->data << " ";
            current = current->next;
        }
        return os;
    }

    Q_Node<T1>* operator[](int index) {
    if (index < 0 || index >= size) {
        return nullptr;  // Return nullptr for invalid index
    }
    Q_Node<T1>* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current;
}

    ~Queue() {
        while (!isEmpty()) {
            Dequeue();
        }
    }

   // The outgoing queue is just a normal queue which actually recieves whatever is dequeued from the priority queue
// dd a ctime library function to make the Dequeue 
//function wait latency_queue_forwarding this variable amount of time(the variable is defined and can be changed from base library file)

    // this is a function that will be used to get the size of the queue
    int getSize() {
        return size;
    }

    // this is a function that will be used to get the head of the queue
    Q_Node<T1>* getHead() {
        return head;
    }

    // this is a function that will be used to get the tail of the queue
    Q_Node<T1>* getTail() {
        return tail;
    }
};

#endif // QUEUE_H
// destination adress variable