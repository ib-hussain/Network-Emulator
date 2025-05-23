#ifndef MESSAGE_H
#define MESSAGE_H
#include "BaseLibrariesFile.h"
struct Message{
    const long long int ID;
    short int priority;
    const String source_address;
    String destination_address;
    const String payload;
    String path;
    Message(String src, String dest = NULLstring, String pl, short int p = NULLint) : payload(pl), ID(++global_ID_declare), source_address(src), destination_address(dest), priority(p)
    {path = src;}
    Message& operator()(String &other){
        path = path + ":" + other;
        return *this;
    }
    Message(Message &other): ID(other.ID), priority(other.priority), source_address(other.source_address), destination_address(other.destination_address), payload(other.payload), path(other.path){}
    Message(Message &other, bool kill=false): ID(other.ID), priority(other.priority), source_address(other.source_address), destination_address(other.destination_address), payload(other.payload), path(other.path){
        if(kill){
            other.~Message();
        }
    }
    Message(Message* other): ID(other->ID), priority(other->priority), source_address(other->source_address), destination_address(other->destination_address), payload(other->payload), path(other->path){}
    Message(): ID(NULLint), priority(NULLint), source_address(NULLstring), destination_address(NULLstring), payload(NULLstring), path(NULLstring){}
    Message& operator=(Message &other){
        if(this != &other){
            ID = other.ID;
            priority = other.priority;
            source_address = other.source_address;
            destination_address = other.destination_address;
            payload = other.payload;
            path = other.path;
        }
        other.destructor();
        return *this;
    }
    ~Message(){
        destructor();
    }
    bool destructor(){
        delete source_address;
        delete destination_address;
        delete payload;
        delete path;
        return true;
    }
    
private:
    friend void writePath(const Message &msg);
    friend ostream& operator<<(ostream &out, const Message &msg){
        out << msg.ID <<':'<<msg.priority<<':'<<msg.source_address<< ':'
            << msg.destination_address << ":\"" << msg.payload << "\":\"" << msg.path<<"\"\n";
        return out;
    }
    String toPathString() const {
        return to_string(ID) + ":\"" + path + "\"";
    }
};

#endif