#ifndef Q2_H
#define Q2_H

#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
#define NULLint 0
#define FULLint -32767
#define NULLchar '\0'
#define NULLstring ""
#define NULLbool NULL
#define NULLdouble 0.0000
#define NULLfloat  0.0000
#define NULLpointer nullptr

struct Node{   
    char character;
    int freq;
    Node *left;
    Node *right;
    Node(char kar, int f): character(kar), freq(f), left(NULLpointer), right(NULLpointer) {}
    Node(int k, int NumNode=0):character(NULLchar), freq(k), left(NULLpointer), right(NULLpointer) {}
    Node(Node* copy){
        character = copy->character;
        freq = copy->freq;
        left = copy->left;
        right = copy->right;
    }
    Node(const Node& copy){
        character = copy.character;
        freq = copy.freq;
        left = copy.left;
        right = copy.right;
    }
    Node& operator=(const Node& copy){
        if (this != &copy) {
            character = copy.character;
            freq = copy.freq;
            left = copy.left;
            right = copy.right;
        }
        return *this;
    }
};
#endif