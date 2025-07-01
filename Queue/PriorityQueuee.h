#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include "../BaseLibrariesFile.h"
#include "../M.h"
template <class PQ_DT1 = Message>
struct PQ_Node
{
private:
    PQ_Node *next;

public:
    PQ_DT1 data;
    PQ_Node(PQ_Node<PQ_DT1> &copy, bool kill = false) : data(copy.data), next(NULLpointer)
    { // killer constructor
        if (kill)
        {
            copy.data.destructor();
        }
    }
    PQ_Node(PQ_DT1 &value) : data(value)
    {
        next = NULLpointer;
    }
    PQ_Node()
    {
        data = PQ_DT1();
        next = NULLpointer;
    }
    PQ_Node(PQ_Node<PQ_DT1> &copy) data(copy.data), priority(copy.priority)
    {
        next = NULLpointer;
    }
    PQ_Node(PQ_Node<PQ_DT1> *copy)
    {
        if (!copy)
        {
            return;
        }
        data = copy->data;
        next = NULLpointer;
    }
    PQ_Node<PQ_DT1> &operator=(const PQ_Node<PQ_DT1> &op)
    {
        if (this != &op)
        {
            data = op.data;
        }
        return *this;
    }
    PQ_Node<PQ_DT1> &operator=(const PQ_Node<PQ_DT1> *op)
    {
        if (this != op)
        {
            data = op->data;
        }
        return *this;
    }
    short int getPriority() const
    {
        return data.priority;
    }
};
template <class PQ_DT2 = Message>
struct PQ
{
public:
    PQ_Node<PQ_DT2> *head;
    int nodes;

public:
    PQ() : head(NULLpointer), nodes(-1) {}
    bool isEmpty() { return head == NULLpointer; }
    // max-priority queue
    // insertion- max-priority
    void insertionMAXpriority(PQ_DT2 &val)
    {
        PQ_Node<PQ_DT2> *NN = new PQ_Node<PQ_DT2>(val);
        if (head == NULLpointer || head->getPriority() < NN->getPriority())
        {
            NN->next = head;
            head = NN;
        }
        else
        {
            PQ_Node<PQ_DT2> *temp = head;
            while (temp->next != NULLpointer && temp->next->getPriority() >= val.priority)
            {
                temp = temp->next;
            }

            NN->next = temp->next;
            temp->next = NN;
        }
    }
    // deletion- max-priority
    void deletionMAXpriority()
    {
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
            return;
        }
        PQ_Node<PQ_DT2> *temp = head;

        head = head->next;
        delete temp;
        temp = NULLpointer;

        PQ_Node<PQ_DT2> *prev = temp;
        while (temp->next != NULLpointer && temp->next->getPriority() >= temp->getPriority())
        {
            prev = temp;
            temp = temp->next;
        }
        prev->next = temp->next;
        delete temp;
        temp = NULLpointer;
    }
    // peek function- max-priority
    PQ_DT2 &peekMAXpriority() const
    {
        PQ_Node<PQ_DT2> *temp = head;
        if (temp == NULLpointer)
        {
            if (debug)
                cout << "Queue is empty" << endl;
            return PQ_DT2();
        }
        while (temp->next != NULLpointer && temp->next->getPriority() >= temp->getPriority())
        {
            temp = temp->next;
        }
        if (debug)
            cout << "highest priority element is: " << temp->data << endl;
        return temp->data;
    }

    // DISPLAY - max-priority
    void displayMAXpriority()
    {
        if (isEmpty())
        {
            if (debug)
                cout << "Queue is empty" << endl;
            return;
        }
        if (debug)
            cout << "Max-Priority Queue: " << endl;
        PQ_Node<PQ_DT2> *temp = head;
        while (temp != NULLpointer)
        {
            if (debug)
                cout << temp->data << " (Priority: " << temp->getPriority() << ") ->";
            temp = temp->next;
        }

        if (debug)
            cout << "NULL";
    }

    // OPERATOR OVERLOADING - max-priority
    PQ_Node<PQ_DT2> &operator[](int key) const
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
        static PQ_Node<PQ_DT2> nullNode(PQ_DT2());
        return nullNode;
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
    bool Enqueue(PQ_DT2 &val)
    {
        if (&val == NULLpointer)
        {
            return false;
        }
        insertionMAXpriority(val);
        return true;
    }

    PQ_DT2 &Dequeue()
    {
        if (isEmpty())
        {
            return PQ_DT2();
        }

        PQ_DT2 highestPriorityElement = peekMAXpriority();

        deletionMAXpriority();

        return highestPriorityElement;
    }
};
#endif