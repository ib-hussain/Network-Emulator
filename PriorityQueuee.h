#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include "BaseLibrariesFile.h"
template <class PQ_DT1 = Message>
struct PQ_Node{
private:
    PQ_Node *next;
    short int priority;
public:
    PQ_DT1 data;
    PQ_Node(PQ_Node<PQ_DT1>& copy, bool kill=false): data(copy.data), next(NULLpointer), priority(copy.priority){ //killer constructor
        if(kill){
            copy.data.destructor();
        }
    }
    PQ_Node(PQ_DT1 value,short int p){
        data = value;
        next = NULLpointer;
        priority=p;
    }
    PQ_Node(){
        data = PQ_DT1();
        next = NULLpointer;
        priority=NULLint;
    }
    PQ_Node(PQ_Node<PQ_DT1>& copy){
        data=copy.data;
        priority = copy.priority;
        next = NULLpointer;
    }
    PQ_Node(PQ_Node<PQ_DT1>* copy){
        if(!copy){
            return;
        }
        data=copy->data;
        priority = copy->priority;
        next = NULLpointer;
    }
    PQ_Node<PQ_DT1>& operator=(const PQ_Node<PQ_DT1>&op){
        if (this!=&op){
            data=op.data;
            priority = op.priority;
        }   
        return *this;
    }
    PQ_Node<PQ_DT1>& operator=(const PQ_Node<PQ_DT1>* op){
        if (this!=op)
        {
            data=op->data;
            priority = op->priority;
        }
        return *this;
    }
    short int getPriority() const 
    { 
        return priority; 
    }
};
template <class PQ_DT2 = Message>
struct PQ{
public:
    PQ_Node<PQ_DT2>* head;
    int nodes;
public:
    PQ():head(NULLpointer), nodes(-1){}
    bool isEmpty(){return head == NULLpointer;}
    // max-priority queue
     // insertion- max-priority
    void insertionMAXpriority(PQ_DT2 val,short int priority) 
    {
        PQ_Node<PQ_DT2> *NN = new PQ_Node<PQ_DT2>(val, priority);
        if (head == NULLpointer || head->getPriority() < NN->getPriority())
        {
            NN->next = head;
            head = NN;
        }
        else
        {
            PQ_Node<PQ_DT2> *temp = head;
            while (temp->next != NULLpointer&&temp->next->getPriority()>=priority)
            {
                temp=temp->next;
            }

            NN->next=temp->next;
            temp->next=NN;
        }
    }
    
    // deletion- max-priority
    void deletionMAXpriority()
     {
        if (isEmpty())
        {
            cout<<"Queue is empty"<<endl;
            return;
        }
        PQ_Node<PQ_DT2> *temp=head;
        if (temp->next==NULLpointer||temp->getPriority()>temp->next->getPriority())
        {
            head=head->next;
            delete temp;
            temp=NULLpointer;
            return;
        }
        PQ_Node<PQ_DT2>*prev=temp;
        while (temp->next!=NULLpointer&&temp->next->getPriority()>=temp->getPriority())
        {
            prev = temp;
            temp = temp->next;
        }
        prev->next = temp->next;
        delete temp;
        temp = NULLpointer;
    }


    // peek function- max-priority
    PQ_DT2& peekMAXpriority()const
    {
        PQ_Node<PQ_DT2>*temp=head;
        if (temp==NULLpointer)
        {
            if(debug)cout<<"Queue is empty"<<endl;
            return PQ_DT2();
        }
        while (temp->next!=NULLpointer&&temp->next->getPriority()>=temp->getPriority())
        {
            temp=temp->next;
        }
        cout<<"highest priority element is: "<<temp->data<<endl;
        return temp->data;
    }

    // DISPLAY - max-priority
    void displayMAXpriority()
    {
        if (isEmpty())
        {
            if(debug)cout << "Queue is empty" << endl;
            return;
        }
        cout << "Max-Priority Queue: " << endl;
        PQ_Node<PQ_DT2> *temp = head;
        while (temp != NULLpointer)
        {
            cout << temp->data << " (Priority: " << temp->getPriority() << ") ->";
            temp = temp->next;
        }

        cout << "NULL";
    }
    
    // OPERATOR OVERLOADING - max-priority
    PQ_Node<PQ_DT2>& operator[](int key) const
    {
        PQ_Node<PQ_DT2> *temp = head;
        int count = 0;
        while (temp)
        {
            if (count == key)
            {
                return *temp;
            }
            temp = temp->next;
            count++;
        }
        return *(new PQ_Node<PQ_DT2>(PQ_DT2(), -1));
    }
    
    // DESTRUCTOR- max-priority
    ~PQ()
     {
        while (!isEmpty()) 
        {
            deletionMAXpriority();
        }
    }

    //---------------------------------------------------------------------------------


   bool Enqueue(PQ_DT2& val, short int priority = 0)
    {
    if (&val==nullptr) 
    {
        return false;
    }
    insertionMAXpriority(val,priority);
    return true;
    }
    
    PQ_DT2& Dequeue()
    {
    if (isEmpty())
     {
        return PQ_DT2();
     }

    PQ_DT2 highestPriorityElement=peekMAXpriority();

    deletionMAXpriority();

    return highestPriorityElement;
    }
};
#endif