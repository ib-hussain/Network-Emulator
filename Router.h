#ifndef ROUTER_H
#define ROUTER_H
#include "PriorityQueue.h"
#include "RoutingTable.h"
#include "Message.h"
#include "SplayTree.h"
template <class incoming0 = Message, class outgoing0 = Message>
struct Router{
    const long long int ID;
    const String name;
    PQ<incoming0> incoming_Queue;
    Queue<outgoing0> outgoing_Queue;
    RoutT routing_table;
    STree<Machine> machine_tree; 
    Router(const String& namei = NULLstring):name(namei), ID(++global_ID_declare), incoming_Queue(), outgoing_Queue(), routing_table(), machine_tree(){}
    Router():name("Default"), ID(NULLint){}
    
};
#endif
//CLI commands
    // take all the data in the fucking commas as input but do parse the whole line and the way i have shown, extract data from it
    // send msg "FILE_NAME.txt"                         //1 type // it will give file name
    // send msgs "FILE_NAME.txt"                        //1 type // it will give file name
    // change RT //4 types:
        // change RT "ROUTER_NAME" add "MACHINE_NAME","ROUTER_NAME"          // gives a name of machine and router & router name
        // change RT "ROUTER_NAME" remove "MACHINE_NAME","ROUTER_NAME"       // gives a name of machine and router & router name
        // change RT "ROUTER_NAME" add "FILE_NAME.csv"                      // gives file name & router name
        // change RT "ROUTER_NAME" remove "FILE_NAME.csv"                   // gives file name & router name
    // print path // 3 types:
        //  has a " to " in between
            // print path "MACHINE_NAME" to "MACHINE_NAME"                  // gives a name of machine and another machine
            // print path "MACHINE_NAME" to "*"                             // gives a name of machine and any other machine
            // print path "*" to "MACHINE_NAME"                             // gives a name of machine and any other machine
    // change egde // implement this in graph.h
        // 4 types:
            // change egde "FILE_NAME.csv"                                  // gives file name
            // change egde "ROUTER_NAME","ROUTER_NAME","WEIGHT"             // gives a name of router and router and weight
            // change egde "MACHINE_NAME","ROUTER_NAME","WEIGHT"            // gives a name of router and router and weight
            // change egde "ROUTER_NAME","MACHINE_NAME","WEIGHT"            // gives a name of router and router and weight
    //add a menu in this whole function