#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H
#include "BaseLibrariesFile.h"
//for the router's linear list and in general as well
template <class idk=Message>
struct box_LL{
    idk data;
    box_LL():data(), next(NULLpointer), prev(NULLpointer){}
    box_LL(idk datai):next(NULLpointer), prev(NULLpointer), data(datai, true){}
    box_LL(box_LL* other):data(other->data), next(NULLpointer), prev(NULLpointer){}
    box_LL(const box_LL& other):data(other.data), next(NULLpointer), prev(NULLpointer){}
    box_LL& operator=(const box_LL& other){
        if(this != &other){
            data = other.data;
            next = NULLpointer;
            prev = NULLpointer;
        }
        return *this;
    }
    box_LL& operator=(box_LL* other){
        if(this != other){
            data = other->data;
            next = NULLpointer;
            prev = NULLpointer;
        }
        return *this;
    }
    box_LL& operator=(const idk& other){
        data = other;
        next = NULLpointer;
        prev = NULLpointer;
        return *this;
    }
    long long int getID()const{
        if(idk == Message || idk== Machine)return data.ID;
        return NULLint;
    }
    ~box_LL(){
        delete data;
        next = NULLpointer;
    }
    friend class Linear_List<idk>;
private:
    box_LL<idk>* next;
    box_LL<idk>* prev;
};
template <class idk1 = Message>
struct Linear_List{
private:
    box_LL<idk1>* head;
    box_LL<idk1>* tail;
    bool delete_at_head(){
        if(!head) return false;
        box_LL<idk1>* temp = head;
        head = head->next;
        if(head) head->prev = NULLpointer;
        else tail = NULLpointer;
        delete temp;
        nodes--;
        return true;
    }
public:
    int nodes;
    Linear_List():head(NULLpointer), tail(NULLpointer), nodes(-1){}
    bool insert(idk1& datai){
        if(!tail){
            box_LL<idk1>* newNode = new box_LL<idk1>(datai);
            tail = newNode;
            head = newNode;
            nodes++;
            return true;
        }
        else{
            box_LL<idk1>* newNode = new box_LL<idk1>(datai);
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
            nodes++;
            return true;
        }
        return false;
    }
    bool delete_this_ID(long long int i_d=NULLint){
        if(i_d == NULLint) return false;
        box_LL<idk1>* current = head;
        while(current){
            if(current->getID() == i_d){
                if(current->prev) current->prev->next = current->next;
                else head = current->next;
                if(current->next) current->next->prev = current->prev;
                else tail = current->prev;
                delete current;
                nodes--;
                return true;
            }
            current = current->next;
        }
        return false;
    }
    bool delete_entry(box_LL<idk1>& entry){
        box_LL<idk1>* current = head;
        while(current){
            if(current == &entry){
                if(current->prev) current->prev->next = current->next;
                else head = current->next;
                if(current->next) current->next->prev = current->prev;
                else tail = current->prev;
                delete current;
                nodes--;
                return true;
            }
            current = current->next;
        }
        return false;
    }
    ~Linear_List(){
        while(head){
            delete_at_head();
        }
    }
    box_LL<Message>& operator[](long long int id_searcher){
        box_LL<Message>* current = head;
        while (current) {
            if (current->getID() == id_searcher) {
                return *current;
            }
            current = current->next;
        }
        static box_LL<Message> passerNode1;
        return passerNode1;
    }
    box_LL<Machine>& operator[](long long int id_searcher){
        box_LL<Machine>* current = head;
        while (current) {
            if (current->getID() == id_searcher) {
                return *current;
            }
            current = current->next;
        }
        static box_LL<Machine> passerNode2;
        return passerNode2;
    }
    box_LL<idk1>& operator[](int index){
        box_LL<idk1>* current = head;
        for(int i = 0; i < index; i++){
            if(!current) return *current;
            current = current->next;
        }
        static box_LL<idk1> passerNode3;
        return passerNode3;
    }
};

#endif