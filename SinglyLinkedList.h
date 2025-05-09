#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H
#include "BaseLibrariesFile.h"
//for the router's linear list
template <class idk=int>
struct box_LL{
    idk data;
    box_LL():id(NULLint), next(NULLpointer), prev(NULLpointer){}
    box_LL(idk datai):id(++global_ID_declare), next(NULLpointer), prev(NULLpointer){
        data = datai;
    }
    ~box_LL(){
        delete data;
        next = NULLpointer;
    }
    friend class Linear_List<idk>;
    long long  int getID()const{
        return id;
    }
private:
    const long long int id;
    box_LL<idk>* next;
    box_LL<idk>* prev;
};
template <class idk1 = int>
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
    bool insert(idk1 datai){
        box_LL<idk1>* newNode = new box_LL<idk1>(datai);
        if(!tail){
            tail = newNode;
            head = newNode;
            nodes++;
            return true;
        }
        else{
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
    ~Linear_List(){
        while(head){
            delete_at_head();
        }
    }
    box_LL<idk1>& operator[](int id_searcher){
        box_LL<idk1>* current = head;
        while (current) {
            if (current->getID() == id_searcher) {
            return *current;
            }
            current = current->next;
        }
        static box_LL<idk1> passerNode1;
        return passerNode1;
    }
};

#endif