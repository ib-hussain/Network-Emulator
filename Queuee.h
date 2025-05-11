#ifndef QUEUE_H
#define QUEUE_H
#include "BaseLibrariesFile.h" 
//perfected------------------------------------------------------------------------
// making a queue class that will be used in the graph class to hold the nodes that are being visited in the graph
// so that we can use any data type in the queue
template <typename T = Message>
struct Q_Node{//node desgigned for queue
    T data;
    Q_Node(T& value): data(value, true){
        this->next = NULLpointer;
    }
    // make default constructor once the datatype for this queue is configured
    friend class Queue<T>;
    ~Q_Node(){// default constructor
        delete data ;
        this->next = NULLpointer;
    }
private:
    Q_Node* next;
};
template <typename T1 = Message>
struct Queue{
private:
    Q_Node<T1> *head;
    Q_Node<T1> *tail;
public:
    int nodes;
    Queue(){
        head = NULLpointer;
        tail = NULLpointer;
        nodes = -1;}
    bool Enqueue(T1& value){
        Q_Node<T1> *nn = new Q_Node<T1>(value);
        if (!head){
            head = nn;
            tail = nn;
            nodes++;
            return true;
        }
        else{
            tail->next = nn;
            tail = nn;
            nodes++;
            return true;
        }
        return false;
    }
    T1& Dequeue(){// Remove redundant check as it duplicates the previous condition
        // Remove redundant check as it duplicates the previous condition
        static T1 NullNode4;
        if (head == NULLpointer) return NullNode4; // base case if queue is empty
        NullNode4 = head->data;
        Q_Node<T1> *temp = head;
        head = head->next;
        delete temp;
        nodes--;
        auto startTime = std::chrono::steady_clock::now();
        std::srand(static_cast<unsigned int>(std::time(NULLpointer)));
        std::this_thread::sleep_for(std::chrono::milliseconds(latency_queue_forwarding));
        return NullNode4;
    }
    bool isEmpty(){return nodes == -1;}
    // friend ostream &operator<<(ostream &os, const Queue<T> &queue){// not a necessary function
    //     Q_Node<T1> *current = Queue.head;
    //     while (current){
    //         os << current->data << " ";
    //         current = current->next;
    //     }
    //     return os;
    // }
    Q_Node<T1>& operator[](int index){
        static Q_Node<T1> NullNode3;
        if (index < 0 || index > nodes) return NullNode3; 
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
#endif