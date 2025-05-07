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

        }
        return false;
    }
    bool remove
public:
    GPtrs(): head(NULLpointer), tail(NULLpointer), nodes(-1) {}
    GPtrsNode& operator[](int i){
        
    }
};


#endif