#ifndef QUEUE_H
#define QUEUE_H
#include "BaseLibrariesFile.h" // Ensure this file exists in the same directory or provide the correct path

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

template <typename T = int>
struct Q_Node{//node desgigned for queue
    // node class that will hold the data and the next pointer
    T data;
    const long long int ID;
    Q_Node(T value): ID(++global_ID_declare){
        this->data = value;
        this->next = NULLpointer;
    }
    friend class Queue<T>;
    ~Q_Node(){// default constructor
        delete data ;
        this->next = NULLpointer;
    }
private:
    Q_Node* next;
};
template <typename T1 = int>
struct Queue{
private:
    Q_Node<T1> *head;
    Q_Node<T1> *tail;
    int size;
public:
    Queue(){
        head = NULLpointer;
        tail = NULLpointer;
        size = -1;}
    bool Enqueue(T1& value){
        Q_Node<T1> *nn = new Q_Node<T1>(value);
        if (!head){
            head = nn;
            tail = nn;
            size++;
            return true;
        }
        else{
            tail->next = nn;
            tail = nn;
            size++;
            return true;
        }
        return false;
    }
    T1& Dequeue(){// Remove redundant check as it duplicates the previous condition
        // Remove redundant check as it duplicates the previous condition
        static T1 NullNode4;
        if (head == NULLpointer) return NullNode4; // base case if
        // queue is empty
        int value = head->data;
        Q_Node<T1> *temp = head;
        head = head->next;
        delete temp;
        size--;
        return value;
    }
    bool isEmpty(){return size == -1;}
    friend ostream &operator<<(ostream &os, const Queue<T> &queue){// not a necessary function
        Q_Node<T1> *current = Queue.head;
        //        Q_Node<int>* current = queue.head;
        while (current != NULL)
        {
            os << current->data << " ";
            current = current->next;
        }
        return os;
    }
    Q_Node<T1>& operator[](int index){
        static Q_Node<T1> NullNode3;
        if (index < 0 || index > size) return NullNode3; 
        Q_Node<T1> *current = head;
        for (int i = 0; i < =index; i++){
            current = current->next;
        }
        return *current;
    }
    ~Queue(){
        while (!isEmpty()){
            Dequqeue();        
        }
        Dequeue(); 
    }
};
// destination adress variable

#endif // QUEUE_H