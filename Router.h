#ifndef ROUTER_H
#define ROUTER_H
#include "Queue.h"
#include "PriorityQueue.h"
#include "RoutingTable.h"

#include "SinglyLinkedList.h"
#include "SplayTree.h"
template <class incoming = int, class outgoing = int, class rt_dtype1 = int>
struct Router{
    PQ<incoming> incoming_Queue;
    Queue<outgoing> outgoing_Queue;
    RoutT<rt_dtype1> routing_table;
    const String name; 
    const long long int ID;
};
#endif