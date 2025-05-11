#ifndef SPLAYTREE_H
#define SPLAYTREE_H
#include "Machine.h"
//perfected------------------------------------------------------------------------
//  make splaying tree:
//  it is almost like AVL,
//  but the difference is that every time a ST_Node is accessed,
//  it is made root, and the rest of the elements are balanced according to the new root in such a manner that this tree also acts as a BST
//  add a bool access variable to the ST_Nodes so a record of last accessed ST_Node can be kept and made into root
//  and for proper funcionality
//  take 2 trees where every new root becomes root of new tree while the old is
// popped onto the new one and deleted, kind of like using 2 queues for
// making 1 stack question from DSA lab sessional
//  and also make a function to check if the tree is empty
//  and also make a function to check if the tree is balanced

template <class D_ST1 = Machine> 
struct ST_Node{
    D_ST1 data;
    ST_Node<D_ST1> *left, *right;
    ST_Node():data(D_ST1()), left(NULLpointer), right(NULLpointer){}
    ST_Node(const D_ST1& data1):data(data1), left(NULLpointer), right(NULLpointer){}
    ST_Node(D_ST1& data1, bool kill=false):data(data1), left(NULLpointer), right(NULLpointer){if(kill){data1.~D_ST1();}}
    ~ST_Node(){
        if constexpr (!is_same_v<D_ST1, long long int>) {
            delete data;
        }
    }
};
template <class D_ST2 = Machine>
struct STree {
    ST_Node<D_ST2>* root;
    STree() : root(NULLpointer) {}
    ~STree() {clear(root);}
    void insert(D_ST2& data) {root = insert(root, data);}
    D_ST2& search(long long int idi = NULLint) {
        D_ST2 temp;
        temp.ID = idi; // temporary object with only ID
        root = splay_by_id(root, idi);
        if (root && root->data.ID == idi) {
            return root->data;
        }
        if(debug)cout<<"Machine with given ID not found."<<endl;
        static D_ST2 NullNode2;
        return NullNode2; 
    }
    D_ST2& operator[](long long int idi = NULLint) {
        D_ST2 temp;
        temp.ID = idi; // temporary object with only ID
        root = splay_by_id(root, idi);
        if (root && root->data.ID == idi) {
            return root->data;
        }
        if(debug)cout<<"Machine with given ID not found."<<endl;
        static D_ST2 NullNode3;
        return NullNode3; 
    }
    void remove(long long int idi) {
        root = remove_by_id(root, idi);
    }
private:
    void clear() {
        clear(root);
        root = NULLpointer;
    }
    ST_Node<D_ST2>* rightRotate(ST_Node<D_ST2>* x) {
        ST_Node<D_ST2>* y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }
    ST_Node<D_ST2>* leftRotate(ST_Node<D_ST2>* x) {
        ST_Node<D_ST2>* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }
    ST_Node<D_ST2>* splay_by_id(ST_Node<D_ST2>* root, long long int idi) {
        if (root == NULLpointer || root->data.ID == idi) return root;
        if (idi < root->data.ID) {
            if (root->left == NULLpointer) return root;
            if (idi < root->left->data.ID) {
                root->left->left = splay_by_id(root->left->left, idi);
                root = rightRotate(root);
            } else if (idi > root->left->data.ID) {
                root->left->right = splay_by_id(root->left->right, idi);
                if (root->left->right != NULLpointer)
                    root->left = leftRotate(root->left);
            }
            return (root->left == NULLpointer) ? root : rightRotate(root);
        } else {
            if (root->right == NULLpointer) return root;
            if (idi < root->right->data.ID) {
                root->right->left = splay_by_id(root->right->left, idi);
                if (root->right->left != NULLpointer)
                    root->right = rightRotate(root->right);
            } else if (idi > root->right->data.ID) {
                root->right->right = splay_by_id(root->right->right, idi);
                root = leftRotate(root);
            }
            return (root->right == NULLpointer) ? root : leftRotate(root);
        }
    }
    ST_Node<D_ST2>* insert(ST_Node<D_ST2>* root, const D_ST2& data) {
        if (root == NULLpointer) return new ST_Node<D_ST2>(data, true);
        root = splay_by_id(root, data.ID);
        if (root->data.ID == data.ID) return root;
        ST_Node<D_ST2>* newNode = new ST_Node<D_ST2>(data, true);
        if (data.ID < root->data.ID) {
            newNode->right = root;
            newNode->left = root->left;
            root->left = NULLpointer;
        } else {
            newNode->left = root;
            newNode->right = root->right;
            root->right = NULLpointer;
        }
        return newNode;
    }
    ST_Node<D_ST2>* remove_by_id(ST_Node<D_ST2>* root, long long int idi) {
        if (root == NULLpointer) return NULLpointer;
        root = splay_by_id(root, idi);
        if (root->data.ID != idi) return root;
        ST_Node<D_ST2>* temp;
        if (root->left == NULLpointer) {
            temp = root;
            root = root->right;
        } else {
            temp = root;
            root = splay_by_id(root->left, idi);
            root->right = temp->right;
        }
        delete temp;
        return root;
    }
    void clear(ST_Node<D_ST2>* node) {
        if (node != NULLpointer) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }
    bool isEmpty() const { return root == NULLpointer; }
    bool isBalanced() const { return isBalanced(root); }
    bool isBalanced(ST_Node<D_ST2>* node) const {
        if (node == NULLpointer) return true;
        int lh = height(node->left);
        int rh = height(node->right);
        return std::abs(lh - rh) <= 1 && isBalanced(node->left) && isBalanced(node->right);
    }
    int height(ST_Node<D_ST2>* node) const {
        if (node == NULLpointer) return 0;
        return 1 + max(height(node->left), height(node->right));
    }
};

#endif