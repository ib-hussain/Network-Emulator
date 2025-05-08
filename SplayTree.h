#ifndef SPLAYTREE_H
#define SPLAYTREE_H
#include "BaseLibrariesFile.h"
// first draft of splaytree implementation

// make splaying tree:
// it is almost like AVL,
// but the difference is that every time a ST_Node is accessed,
// it is made root, and the rest of the elements are balanced according to the new root in such a manner that this tree also acts as a BST
// add a bool access variable to the ST_Nodes so a record of last accessed ST_Node can be kept and made into root
// and for proper funcionality, take 2 trees where every new root becomes root of new tree while the old is popped onto the new one and deleted, kind of like using 2 queues for stacks
struct ST_Node
{
    int key;
    ST_Node *left, *right;
};
struct STree
{
    ST_Node *newST_Node(int key)
    {
        ST_Node *ST_Node = new ST_Node();
        ST_Node->key = key;
        ST_Node->left = ST_Node->right = nullptr;
        return ST_Node;
    }

    ST_Node *rightRotate(ST_Node *x)
    {
        ST_Node *y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }

    ST_Node *leftRotate(ST_Node *x)
    {
        ST_Node *y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }

    ST_Node *splay(ST_Node *root, int key)
    {
        if (root == nullptr || root->key == key)
            return root;

        if (root->key > key)
        {
            if (root->left == nullptr)
                return root;
            if (root->left->key > key)
            {
                root->left->left = splay(root->left->left, key);
                root = rightRotate(root);
            }
            else if (root->left->key < key)
            {
                root->left->right = splay(root->left->right, key);
                if (root->left->right != nullptr)
                    root->left = leftRotate(root->left);
            }
            return (root->left == nullptr) ? root : rightRotate(root);
        }
        else
        {
            if (root->right == nullptr)
                return root;
            if (root->right->key > key)
            {
                root->right->left = splay(root->right->left, key);
                if (root->right->left != nullptr)
                    root->right = rightRotate(root->right);
            }
            else if (root->right->key < key)
            {
                root->right->right = splay(root->right->right, key);
                root = leftRotate(root);
            }
            return (root->right == nullptr) ? root : leftRotate(root);
        }
    }

    ST_Node *insert(ST_Node *root, int key)
    {
        if (root == nullptr)
            return newST_Node(key);

        root = splay(root, key);

        if (root->key == key)
            return root;

        ST_Node *ST_Node = newST_Node(key);
        if (root->key > key)
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

    void preOrder(ST_Node *ST_Node)
    {
        if (ST_Node != nullptr)
        {
            cout << ST_Node->key << " ";
            preOrder(ST_Node->left);
            preOrder(ST_Node->right);
        }
    }
};

#endif