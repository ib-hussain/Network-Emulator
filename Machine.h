#ifndef MACHINE_H
#define MACHINE_H
#include "Queuee.h"

struct Machine{
    const String name;
    const long long int ID;
    Queue<Message> incoming;
    Queue<Message> outgoing;
    Machine(const String& namei = NULLstring):name(namei), ID(++global_ID_declare), incoming(), outgoing(){}//original
    Machine(Machine& other):name(other.name), ID(other.ID), incoming(other.incoming), outgoing(other.outgoing){}//copy
    Machine():name("Default"), ID(NULLint){}//default
    bool EmptyQueue(int level=NULLint){
        // empty the whole outgoing queue here accoridng to the provided amount or maybe the whole queue
        // outgoing.Dequeue(true);
    }
    bool recieveMessage(){}
};

#endif