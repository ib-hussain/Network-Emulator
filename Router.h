#ifndef ROUTER_H
#define ROUTER_H
#include "Queue.h"
#include "PriorityQueue.h"
#include "RoutingTable.h"

#include "SplayTree.h"
template <class incoming = Message, class outgoing = Message, class rt_dtype1 = int>
struct Router{
    const long long int ID;
    PQ<incoming> incoming_Queue;
    Queue<outgoing> outgoing_Queue;
    RoutT<rt_dtype1> routing_table;// configure default datatype
    const String name; 
    Router(const String& namei = NULLstring):name(namei), ID(++global_ID_declare){}
    
};
#endif