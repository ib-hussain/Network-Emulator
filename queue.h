#include "BaseLibrariesFile.h" // Ensure this file exists in the same directory or provide the correct path
#ifndef QUEUE_H
#define QUEUE_H


#include <stdexcept> // Include for runtime_error
#include <iostream>  // Include for ostream
using namespace std; // Ensure standard namespace is used
// Ensure this file exists in the same directory as queue.h         // Include for ostream
// making a queue class that will be used in the graph class to hold the nodes that are being visited in the graph
// this is a circular linked list that will hold the nodes that are being visited in the graph
// using templates 
// so that we can use any data type in the queue
// this is a singly linked list that will hold the nodes that are being visited in the graph


//class node()
// static full int x -1  var node - id enhancer 

const int FULL_INT = -32767; // constant to hold the value of the full int
// this is a constant that will be used to check if the queue is empty or not

template <typename T=int>
    struct queue_node{
        // node class that will hold the data and the next pointer
        T data;
        long int ID;
        static long long int enhancer;
        queue_node* next;
        queue_node(T value){
            this->data = value;
            this->next = NULL;
            ID=1+enhancer;
            enhancer++; // ID of the node is set to 1 + enhancer
        }


    };
template <typename T>
long long int queue_node<T>::enhancer = -1 * FULL_INT; // static variable to hold the ID of the node
    template <typename T>
    struct q_node{
        queue_node<T>* head;
        queue_node<T>* tail;
        int size;
        q_node()
        {
            head = NULL;
            tail = NULL;
            size = 0; }
        void enqueue(T value)
        {
            queue_node<T>* nn = new queue_node<T>(value);
            if(head == NULL)
            {
                head = nn;
                tail = nn;
            }else
            {
                tail->next = nn;
                tail = nn;
            }
            size++;
        }
        T dequeue()
            // Remove redundant check as it duplicates the previous condition
        {
            // Remove redundant check as it duplicates the previous condition
            // if(head == NULL) return -1; // base case if 
            if(head == NULL) return -1; // base case if 
            //queue is empty
            int value = head->data;
            queue_node<int>* temp = head;
            head = head->next;
            delete temp;
            size--;
            return value;
        }
        bool isEmpty(){
            return size == 0;
        }

    friend ostream& operator<<(ostream& os, const q_node<T>& queue) {
        queue_node<T>* current = queue.head;
        //        queue_node<int>* current = queue.head;
        while (current != NULL) {
            os << current->data << " ";
            current = current->next;
        }
        return os;
    }
};

//destination adress variable 

#endif // QUEUE_H

   
