#ifndef MACHINE_H
#define MACHINE_H
#include "Queuee.h"

struct Machine{
    const String name;
    const long long int ID;
    Queue<Message> incoming_Queue;
    Queue<Message> outgoing_Queue;
    Machine(const String& namei = NULLstring):name(namei), ID(++global_ID_declare), incoming_Queue(), outgoing_Queue(){}
    Machine():name("Default"), ID(NULLint){}
    
};

#endif