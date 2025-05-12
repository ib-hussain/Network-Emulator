#ifndef GPTRSNODE_H
#define GPTRSNODE_H
#include "GraphNode.h"
#include "BaseLibrariesFile.h"
template <class D_Grphi2 = Router>
struct GPtrsNode{
    int weight;
    GraphNode<D_Grphi2>* connection;
    GPtrsNode(): weight(NULLint), connection(NULLpointer),  nextnode(NULLpointer) {}
    GPtrsNode(int weighti, GraphNode<D_Grphi2>* nexti): weight(weighti), connection(nexti) , nextnode(NULLpointer) {}
    //xfcvgh
    friend class GPtrs<D_Grphi2>;
    ~GPtrsNode(){
        weight = NULLint;
        connection= NULLpointer ;
        nextnode = NULLpointer;
    }
    int& operator*(){
        return weight;
    }
    GraphNode<D_Grphi2>* operator>>(int i=NULLint){
        return connection;
    }
private:
    GPtrsNode<D_Grphi2>* nextnode;
};
#endif