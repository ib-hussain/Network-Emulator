#ifndef LLNODE_H
#define LLNODE_H
#include "GPtrs.h"
template <class D_Grphi5 = String>
struct LLNode{
    D_Grphi5 data;//make this template later
    LLNode():data(NULLint-1), left(NULLpointer), right(NULLpointer), up(NULLpointer), down(NULLpointer){}
    LLNode(D_Grphi5 datai):data(datai), left(NULLpointer), right(NULLpointer), up(NULLpointer), down(NULLpointer){}
    ~LLNode(){
        left = NULLpointer;
        right = NULLpointer;
        up = NULLpointer;
        down = NULLpointer;
        delete data;
    }
    LLNode<D_Grphi5>& operator=(const LLNode<D_Grphi5>& other){
        data = other.data;
        return *this;
    }
    LLNode<D_Grphi5>& operator=(const D_Grphi5& other){
        data = other;
        return *this;
    }
    friend class D2LL<D_Grphi5>;
private:
    LLNode* left;
    LLNode* right;
    LLNode* up;
    LLNode* down;
};
#endif