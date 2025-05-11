#ifndef ROUTER_H
#define ROUTER_H
#include "PriorityQueue.h"
#include "RoutingTable.h"

#include "SplayTree.h"
template <class incoming0 = Message, class outgoing0 = Message>
struct Router{
    const long long int ID;
    const String name;
    PQ<incoming0> incoming_Queue;
    Queue<outgoing0> outgoing_Queue;
    RoutT routing_table;
    STree<Machine> machine_tree; 
    Router(const String& namei = NULLstring):name(namei), ID(++global_ID_declare), incoming_Que {}
    Router():name("Default"), ID(NULLint){}
};
#endif