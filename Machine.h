#ifndef MACHINE_H
#define MACHINE_H
#include "Queuee.h"
#include "BaseLibrariesFile.h"
//perfected------------------------------------------------------------------------
struct Machine{
    const String name;
    const long long int ID;
    int weightage;
    Queue<Message> incoming;
    Queue<Message> outgoing;
    Machine(const String& namei = NULLstring, int wt):name(namei), ID(++global_ID_declare), incoming(), outgoing(), weightage(wt){}//original
    Machine(Machine& other):name(other.name), ID(other.ID), incoming(other.incoming), outgoing(other.outgoing), weightage(other.weightage){}//copy
    Machine(Machine* other):name(other->name), ID(other->ID), incoming(other->incoming), outgoing(other->outgoing){}//copy
    Machine(Machine& other, bool kill=false):name(other.name), ID(other.ID), incoming(other.incoming), outgoing(other.outgoing){//killer
        if(kill){
            other.~Machine();
        }
    }
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
    ~Machine(){
        while(!incoming.isEmpty()){
            read_messages_finally();
        }
        while(!outgoing.isEmpty()){
            send_a_message();
        }
        delete name;
        incoming.~Queue();
        outgoing.~Queue();
    }
};

#endif