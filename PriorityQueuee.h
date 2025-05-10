#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include "BaseLibrariesFile.h"
template <class PQ_DT1 = Message>
struct PQ_Node{
private:
    PQ_Node *next;
public:
    PQ_DT1 data;
    PQ_Node(PQ_DT1 value){
        data = value;
        next = NULLpointer;
    }
    PQ_Node(){
        data = PQ_DT1();
        next = NULLpointer;
    }
    PQ_Node(PQ_Node<PQ_DT1>& copy){
        data=copy.data;
    }
    PQ_Node(PQ_Node<PQ_DT1>* copy){
        if(!copy){
            return;
        }
        data=copy.data;
    }
    PQ_Node<PQ_DT1>& operator=(const PQ_Node<PQ_DT1>&op){
        if (this!=&op){
            data=op.data;
        }   
        return *this;
    }
    PQ_Node<PQ_DT1>& operator=(const PQ_Node<PQ_DT1>* op){
        if (this!=op){
            data=op->data;
        }
        return *this;
    }
};
template <class PQ_DT2 = Message>
struct PQ{
private:
    PQ_Node<PQ_DT2>* head;
    int nodes;
public:
    PQ():head(NULLpointer), nodes(-1){}
    bool isEmpty(){return head == NULLpointer;}
    // max-priority queue // insertion- max-priority
    bool Enqueue(PQ_DT2& val){// insertionMAXpriority
        // bool tells if the data was inserted or not
    }
    // deletion- max-priority
    PQ_DT2& Dequeue(){
        if (isEmpty())
        {
            return (PQ_DT2());
        }
        
    }
    // OPERATOR OVERLOADING - max-priority
    PQ_Node<PQ_DT2>& operator[](int IDi){
        //search by id of message 
    }
    // DESTRUCTOR- max-priority
    ~PQ(){
        while (!isEmpty()){
            Dequeue();
        }
    }
};
#endif