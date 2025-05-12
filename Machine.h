#ifndef MACHINE_H
#define MACHINE_H
#include "Queuee.h"
//perfected------------------------------------------------------------------------
struct Machine{
    const String name;
    const long long int ID;
    Queue<Message> incoming;
    Queue<Message> outgoing;
    Machine(const String& namei = NULLstring):name(namei), ID(++global_ID_declare), incoming(), outgoing(){}//original
    Machine(Machine& other):name(other.name), ID(other.ID), incoming(other.incoming), outgoing(other.outgoing){}//copy
    Machine():name("Default"), ID(NULLint){}//default
    Message& send_a_message(){
        return outgoing.Dequeue(true);
    }
    Message& recieve_message(Message& newmessage){
        return incoming.Enqueue(newmessage);
    }
    Message& recieve_message(Message* newmessage){
        bool abc = incoming.Enqueue((*newmessage));
        delete newmessage;
        return abc; 
    }
    Message& recieve_message(String src, String dest = NULLstring, String pl, short int p = NULLint){
        return incoming.Enqueue(Message(src, dest, pl, p));
    }
    bool read_messages_finally(){
        // dequeue the whole incoming queue here into a file named recieved_messages.txt
        // by overloading the out file stream operator in messages structure
        Message msg;
        while(!incoming.isEmpty()){
            msg = incoming.Dequeue();
            writeMessage(msg);
            writePath(msg);
            // process the message
        }
        return true;
    }
};

#endif