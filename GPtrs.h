#ifndef GPTRS_H
#define GPTRS_H
#include "GPtrsNode.h"
#include "BaseLibrariesFile.h"
template <class D_Grphi3 = Router>
struct GPtrs{
private:
    // this is a singly circular linked list that stores the pointers to the other nodes in the graph
    GPtrsNode<D_Grphi3>* tail;
    int nodes;
    
public:
    GPtrs(): tail(NULLpointer), nodes(0) {}
    bool insert(GraphNode<D_Grphi3>* newNode, int weighti){
        if(!tail){
            tail = new GPtrsNode<D_Grphi3>(weighti, newNode);
            tail->nextnode = tail;
            nodes++;
            return true;
        }
        else{
            GPtrsNode<D_Grphi3>* newNodePtr = new GPtrsNode<D_Grphi3>(weighti, newNode);
            newNodePtr->nextnode = tail->nextnode;
            tail->nextnode = newNodePtr;
            tail = newNodePtr;
            nodes++;
            return true;
        }
        return false;
    }
    bool remove(GraphNode<D_Grphi3>* node){
        if(!tail) return false;
        GPtrsNode<D_Grphi3>* current = tail->nextnode;
        GPtrsNode<D_Grphi3>* previous = tail;
        do{
            if(current->connection == node){
                if(current == tail){
                    tail = previous;
                }
                previous->nextnode = current->nextnode;
                delete current;
                nodes--;
                return true;
            }
            previous = current;
            current = current->nextnode;
        }while(current != tail->nextnode);
        return false;
    }
    bool ifempty(){
        return (tail == NULLpointer);
    }
    GPtrsNode<D_Grphi3>& operator[](int i){
        static GPtrsNode<D_Grphi3> NullNode;
        if(i < 0 || i >= nodes) return NullNode;
        GPtrsNode<D_Grphi3>* current = tail->nextnode;
        for(int j = 0; j < i; j++){
            current = current->nextnode;
        }
        return (*current);
    }
    GPtrsNode<D_Grphi3>& operator[](GraphNode<D_Grphi3>* node){
        static GPtrsNode<D_Grphi3> NullNode1;
        if(ifempty()) return NullNode1;
        GPtrsNode<D_Grphi3>* current = tail->nextnode;
        do{
            if(current->connection == node) return (*current);
            current = current->nextnode;
        }while(current != tail->nextnode);
        return NullNode1;
    }
    ~GPtrs(){
        if(tail) {
            GPtrsNode<D_Grphi3>* current = tail->nextnode;
            GPtrsNode<D_Grphi3>* next = NULLpointer;
            do{
                next = current->nextnode;
                delete current;
                current = next;
            }while(current != tail->nextnode);
            delete tail;
        }
    }
    friend class Graph<D_Grphi3>;
};
#endif