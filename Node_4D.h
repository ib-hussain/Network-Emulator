#ifndef NODE_4D_H
#define NODE_4D_H
#include "GPtrs.h"
#include "String/String.h"
template <class D_Grphi5 = String>
struct Node_4D{
    D_Grphi5 data;//make this template later
    Node_4D():data(NULLint-1), left(NULLpointer), right(NULLpointer), up(NULLpointer), down(NULLpointer){}
    Node_4D(D_Grphi5 datai):data(datai), left(NULLpointer), right(NULLpointer), up(NULLpointer), down(NULLpointer){}
    ~Node_4D(){
        left = NULLpointer;
        right = NULLpointer;
        up = NULLpointer;
        down = NULLpointer;
        delete data;
    }
    Node_4D<D_Grphi5>& operator=(const Node_4D<D_Grphi5>& other){
        data = other.data;
        return *this;
    }
    Node_4D<D_Grphi5>& operator=(const D_Grphi5& other){
        data = other;
        return *this;
    }
    friend class D2LL<D_Grphi5>;
private:
    Node_4D* left;
    Node_4D* right;
    Node_4D* up;
    Node_4D* down;
};
#endif