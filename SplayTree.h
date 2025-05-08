#ifndef SPLAYTREE_H
#define SPLAYTREE_H
#include "BaseLibrariesFile.h"
// first draft of splaytree implementation

// make splaying tree:
// it is almost like AVL,
// but the difference is that every time a ST_Node is accessed,
// it is made root, and the rest of the elements are balanced according to the new root in such a manner that this tree also acts as a BST
// add a bool access variable to the ST_Nodes so a record of last accessed ST_Node can be kept and made into root
// and for proper funcionality, take 2 trees where every new root becomes root of new tree while the old is popped onto the new one and deleted, kind of like using 2 queues for making 1 stack question from DSA lab sessional
template <class D_ST1 = int>//configure if this type is okay for this project
struct ST_Node
{
    D_ST1 data;
    ST_Node *left, *right;
    bool last_accessed = false; // this is the variable that will be used to keep track of the last accessed ST_Node
    ST_Node() : data(NULLint), left(NULLpointer), right(NULLpointer) {}
    ST_Node(D_ST1 data1) : data(data1), left(NULLpointer), right(NULLpointer) {}
};
template <class D_ST2 = int>//configure if this type is okay for this project
struct STree
{
    ST_Node<D_ST2>* newST_Node(int data)
    {
        ST_Node<D_ST2>* ST_Node = new ST_Node<D_ST2>();
        ST_Node->data = data;
        ST_Node->left = ST_Node->right = nullptr;
        return ST_Node;
    }
    ST_Node<D_ST2>* rightRotate(ST_Node<D_ST2>* x)
    {
        ST_Node *y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }

    ST_Node<D_ST2>* leftRotate(ST_Node<D_ST2>* x)
    {
        ST_Node *y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }

    ST_Node<D_ST2>* splay(ST_Node<D_ST2>* root, int data)
    {
        if (root == nullptr || root->data == data)
            return root;

        if (root->data > data)
        {
            if (root->left == nullptr)
                return root;
            if (root->left->data > data)
            {
                root->left->left = splay(root->left->left, data);
                root = rightRotate(root);
            }
            else if (root->left->data < data)
            {
                root->left->right = splay(root->left->right, data);
                if (root->left->right != nullptr)
                    root->left = leftRotate(root->left);
            }
            return (root->left == nullptr) ? root : rightRotate(root);
        }
        else
        {
            if (root->right == nullptr)
                return root;
            if (root->right->data > data)
            {
                root->right->left = splay(root->right->left, data);
                if (root->right->left != nullptr)
                    root->right = rightRotate(root->right);
            }
            else if (root->right->data < data)
            {
                root->right->right = splay(root->right->right, data);
                root = leftRotate(root);
            }
            return (root->right == nullptr) ? root : leftRotate(root);
        }
    }

    ST_Node<D_ST2>* insert(ST_Node<D_ST2>* root, int data)
    {
        if (root == nullptr)
            return newST_Node(data);

        root = splay(root, data);

        if (root->data == data)
            return root;

        ST_Node *ST_Node = newST_Node(data);
        if (root->data > data)
        {
            ST_Node->right = root;
            ST_Node->left = root->left;
            root->left = nullptr;
        }
        else
        {
            ST_Node->left = root;
            ST_Node->right = root->right;
            root->right = nullptr;
        }
        return ST_Node;
    }

    void preOrder(ST_Node<D_ST2>* ST_Node1)
    {
        if (ST_Node1 != nullptr)
        {
            cout << ST_Node1->data << " ";
            preOrder(ST_Node1->left);
            preOrder(ST_Node1->right);
        }
    }
};

#endif