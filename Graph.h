#ifndef GRAPH_H
#define GRAPH_H
#include "BaseLibrariesFile.h"
template <class dtype1 = int>//configure isf this type is okay for this project
struct GraphNode{
    dtype data;// this can be any datatype we choose to use in the graph
    GPtrs pointers;
    // i am making 1 graph node and making a linked list in it that holds the pointers to the other nodes in the graph
    // this is a singly linked list of pointers to the other nodes in the graph
};
struct GPtrsNode{
    int weight;
    GraphNode* connection;
    GPtrsNode(): weight(NULLint), connection(NULLpointer),  nextnode(NULLpointer) {}
    GPtrsNode(int weighti, GraphNode* nexti): weight(weighti), connection(nexti) , nextnode(NULLpointer) {}
    
    friend class GPtrs;
    int& operator*(){
        return weight;
    }
    GraphNode* operator>>(int i=NULLint){
        return connection;
    }
private:
    GPtrsNode* nextnode;
};
struct GPtrs{
private:
    // this is a singly circular linked list that stores the pointers to the other nodes in the graph
    GPtrsNode* tail;
    int nodes;
    bool insert(GraphNode* newNode, int weighti){
        if(!tail){
            tail = new GPtrsNode(weighti, newNode);//fix this constructor call here
            tail->nextnode = tail;
            nodes++;
            return true;
        }
        else{
            GPtrsNode* newNode = new GPtrsNode(weighti, newNode);
            newNode->nextnode = tail->nextnode;
            tail->nextnode = newNode;
            tail = newNode;
            nodes++;
            return true;
        }
        return false;
    }
    bool remove(GraphNode* node){
        if(!tail) return false;
        GPtrsNode* current = tail->nextnode;
        GPtrsNode* previous = tail;
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
public:
    GPtrs(): head(NULLpointer), tail(NULLpointer), nodes(-1) {}
    GPtrsNode& operator[](int i){
        static GPtrsNode NullNode;
        if(i < 0 || i >= nodes) return NullNode;
        GPtrsNode* current = tail->nextnode;
        for(int j = 0; j < i; j++){
            current = current->nextnode;
        }
        return (*current);
    }
    GPtrsNode& operator[](GraphNode* node){
        static GPtrsNode NullNode;
        if(ifempty()) return NullNode;
        GPtrsNode* current = tail->nextnode;
        do{
            if(current->connection == node) return (*current);
            current = current->nextnode;
        }while(current != tail->nextnode);
        return NullNode;
    }
    ~GPtrs(){
        GPtrsNode* current = tail->nextnode;
        GPtrsNode* next = NULLpointer;
        do{
            next = current->nextnode;
            delete current;
            current = next;
        }while(current != tail->nextnode);
        delete tail;
    }
};
// cgvhbjnm
struct Graph{
    GraphNode* top;


}



#endif