#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include "Router.h"
#include "BaseLibrariesFile.h"
template <class D_Grphi1 = Router>
struct GraphNode{
    D_Grphi1 data;// this will have the name and the id itself
    GPtrs<D_Grphi1> pointers;
    // i am making 1 graph node and making a linked list in it that holds the pointers to the other nodes in the graph
    // this is a singly circular linked list of pointers to the other nodes in the graph
    GraphNode(D_Grphi1 datai):data(datai), pointers(){}// this is the only constructor
    ~GraphNode(){
        delete data;
        delete pointers;
    }
};
#endif