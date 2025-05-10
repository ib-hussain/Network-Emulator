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
public:
    PQ_Node<PQ_DT2>* head;
    PQ(){head = NULLpointer;}
    bool isEmpty(){return head == NULLpointer;}
    // max-priority queue
    // insertion- max-priority
    void insertionMAXpriority(PQ_DT2 val, short int priority){
        PQ_Node<PQ_DT2> *NN = new PQ_Node<PQ_DT2>(val, priority);
        if (head == NULLpointer || head->priority < NN->priority)
        {
            NN->next = head;
            head = NN;
        }
        else
        {
            PQ_Node<PQ_DT2> *temp = head;
            while (temp->next != NULLpointer && temp->next->priority >= priority)
            {
                temp = temp->next;
            }

            NN->next = temp->next;
            temp->next = NN;
        }
    }
    // deletion- max-priority
    void deletionMAXpriority(){
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
            return PQ_DT2();
        }
        PQ_Node<PQ_DT2> *temp = head;
        if (temp->next == NULLpointer || temp->priority > temp->next->priority)
        {
            head = head->next;
            delete temp;
            temp = NULLpointer;
            return;
        }
        PQ_Node<PQ_DT2> *prev = temp;
        while (temp->next != NULLpointer && temp->next->priority >= temp->priority)
        {

            prev = temp;
            temp = temp->next;
        }
        prev->next = temp->next;
        delete temp;
        temp = NULLpointer;
    }
    // peek function- max-priority
    PQ_DT2 peekMAXpriority() const
    {
        PQ_Node<PQ_DT2> *temp = head;
        if (temp == NULLpointer)
        {
            cout << "Queue is empty" << endl;
            return PQ_DT2();
        }
        while (temp->next != NULLpointer && temp->next->priority >= temp->priority)
        {
            temp = temp->next;
        }
        cout << "highest priority element is: " << temp->data << endl;
        return temp->data;
    }

    // DISPLAY - max-priority
    void displayMAXpriority()
    {
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
            return;
        }
        cout << "Max-Priority Queue: " << endl;
        PQ_Node<PQ_DT2> *temp = head;
        while (temp != NULLpointer)
        {
            cout << temp->data << " (Priority: " << temp->priority << ") ->";
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
        // cout << "invalid position: " << key << endl;
        return *(new PQ_Node<PQ_DT2>(PQ_DT2(), -1));
    }
    // DESTRUCTOR- max-priority
    ~PQ(){
        while (!isEmpty()){
            deletionMAXpriority();
        }
    }
};
#endif