#ifndef GRAPH_H
#define GRAPH_H
#include "BaseLibrariesFile.h"
template <class D_Grphi1 = int>//configure if this type is okay for this project
struct GraphNode{
    D_Grphi1 data;// this can be any datatype we choose to use in the graph
    GPtrs<D_Grphi1> pointers;
    // dfghjk
    // GraphNode():data(NULLint){}//make proper constreuctor later
    // i am making 1 graph node and making a linked list in it that holds the pointers to the other nodes in the graph
    // this is a singly linked list of pointers to the other nodes in the graph
};
template <class D_Grphi2 = int>//configure if this type is okay for this project
struct GPtrsNode{
    int weight;
    GraphNode<D_Grphi2>* connection;
    GPtrsNode(): weight(NULLint), connection(NULLpointer),  nextnode(NULLpointer) {}
    GPtrsNode(int weighti, GraphNode<D_Grphi2>* nexti): weight(weighti), connection(nexti) , nextnode(NULLpointer) {}
    //xfcvgh
    friend class GPtrs<D_Grphi2>;
    int& operator*(){
        return weight;
    }
    GraphNode<D_Grphi2>* operator>>(int i=NULLint){
        return connection;
    }
private:
    GPtrsNode<D_Grphi2>* nextnode;
};
template <class D_Grphi3 = int>//configure if this type is okay for this project
struct GPtrs{
private:
    // this is a singly circular linked list that stores the pointers to the other nodes in the graph
    GPtrsNode<D_Grphi3>* tail;
    int nodes;
    bool insert(GraphNode<D_Grphi3>* newNode, int weighti){
        if(!tail){
            tail = new GPtrsNode<D_Grphi3>(weighti, newNode);//fix this constructor call here
            tail->nextnode = tail;
            nodes++;
            return true;
        }
        else{
            GPtrsNode* newNode = new GPtrsNode<D_Grphi3>(weighti, newNode);
            newNode->nextnode = tail->nextnode;
            tail->nextnode = newNode;
            tail = newNode;
            nodes++;
            return true;
        }
        return false;
    }
    bool remove(GraphNode<D_Grphi3>* node){
        if(!tail) return false;
        GPtrsNode<D_Grphi3>* current = tail->nextnode;
        GPtrsNode<D_Grphi3>* previous = tail;
        do{
            if(current->connection == node){
                if(current == tail){
                    tail = previous;
                }
                previous->nextnode = current->nextnode;
                delete current;
                nodes--;
                return true;
            }
            previous = current;
            current = current->nextnode;
        }while(current != tail->nextnode);
        return false;
    }
    bool ifempty(){
        return (tail == NULLpointer);
    }
public:
    GPtrs(): head(NULLpointer), tail(NULLpointer), nodes(-1) {}
    GPtrsNode<D_Grphi3>& operator[](int i){
        static GPtrsNode<D_Grphi3> NullNode;
        if(i < 0 || i >= nodes) return NullNode;
        GPtrsNode<D_Grphi3>* current = tail->nextnode;
        for(int j = 0; j < i; j++){
            current = current->nextnode;
        }
        return (*current);
    }
    GPtrsNode<D_Grphi3>& operator[](GraphNode<D_Grphi3>* node){
        static GPtrsNode<D_Grphi3> NullNode;
        if(ifempty()) return NullNode;
        GPtrsNode<D_Grphi3>* current = tail->nextnode;
        do{
            if(current->connection == node) return (*current);
            current = current->nextnode;
        }while(current != tail->nextnode);
        return NullNode;
    }
    ~GPtrs(){
        GPtrsNode<D_Grphi3>* current = tail->nextnode;
        GPtrsNode<D_Grphi3>* next = NULLpointer;
        do{
            next = current->nextnode;
            delete current;
            current = next;
        }while(current != tail->nextnode);
        delete tail;
    }
};
struct LLNode{
    int data;//make this template later
    LLNode* left;
    LLNode* right;
    LLNode* up;
    LLNode* down;
    LLNode():data(NULLint), left(NULLpointer), right(NULLpointer), up(NULLpointer), down(NULLpointer){}
    LLNode(int datai):data(datai), left(NULLpointer), right(NULLpointer), up(NULLpointer), down(NULLpointer){}
};
struct D2LL{
private:
    LLNode** o0_0o;
    int rows;
    int columns;
public:
    2DLL(){
        o0_0o = NULLpointer;
    }
    bool initialise(int rows1, int columns1){
        if(rows1 <= 0 || columns1 <= 0) return false;
        rows = rows1;
        columns = columns1;
        o0_0o = new LLNode*[rows];
        for(int i = 0; i < rows; i++){
            o0_0o[i] = new LLNode[columns];
            for(int j = 0; j < columns; j++){
                o0_0o[i][j].left = (j == 0) ? NULLpointer : &o0_0o[i][j-1];
                o0_0o[i][j].right = (j == columns-1) ? NULLpointer : &o0_0o[i][j+1];
                o0_0o[i][j].up = (i == 0) ? NULLpointer : &o0_0o[i-1][j];
                o0_0o[i][j].down = (i == rows-1) ? NULLpointer : &o0_0o[i+1][j];
            }
        }
        return true;
    }
    bool resize(int rows1, int columns1){
        if(rows1 <= 0 || columns1 <= 0) return false;
        LLNode** new_o0_0o = new LLNode*[rows1];
        for(int i = 0; i < rows1; i++){
            new_o0_0o[i] = new LLNode[columns1];
            for(int j = 0; j < columns1; j++){
                if(i < rows && j < columns){
                    new_o0_0o[i][j] = o0_0o[i][j];
                }
                else{
                    new_o0_0o[i][j].left = (j == 0) ? NULLpointer : &new_o0_0o[i][j-1];
                    new_o0_0o[i][j].right = (j == columns1-1) ? NULLpointer : &new_o0_0o[i][j+1];
                    new_o0_0o[i][j].up = (i == 0) ? NULLpointer : &new_o0_0o[i-1][j];
                    new_o0_0o[i][j].down = (i == rows1-1) ? NULLpointer : &new_o0_0o[i+1][j];
                }
            }
        }
        for(int i = 0; i < rows; i++){
            delete[] o0_0o[i];
        }
        delete[] o0_0o;
        o0_0o = new_o0_0o;
        rows = rows1;
        columns = columns1;
        return true;
    }
    LLNode& get(int i, int j){
        if(i < 0 || i >= rows || j < 0 || j >= columns) return NULLpointer;
        return o0_0o[i][j];
    }
    ~LLNode(){
        for(int i = 0; i < rows; i++){
            delete[] o0_0o[i];
        }
        delete[] o0_0o;
    }
};
template <class D_Grphi4 = int>//configure if this type is okay for this project
struct Graph{
    GraphNode<D_Grphi4>* top;
    int nodes;
    D2LL connection_list;
    Graph():top(NULLpointer){
    }
    bool insert(int data, int to_which node){
        top->
    }
};


#endif