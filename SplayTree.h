#ifndef SPLAYTREE_H
#define SPLAYTREE_H
#include "BaseLibrariesFile.h"
// first draft of splaytree implementation

// make splaying tree:
// it is almost like AVL, 
// but the difference is that every time a node is accessed, 
// it is made root, and the rest of the elements are balanced according to the new root in such a manner that this tree also acts as a BST
// add a bool access variable to the nodes so a record of last accessed node can be kept and made into root
// and for proper funcionality, take 2 trees where every new root becomes root of new tree while the old is popped onto the new one and deleted, kind of like using 2 queues for stacks
struct Node {
    int key;
    Node *left, *right;
};

Node* newNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = node->right = nullptr;
    return node;
}

Node* rightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

Node* splay(Node* root, int key) {
    if (root == nullptr || root->key == key)
        return root;

    if (root->key > key) {
        if (root->left == nullptr)
            return root;
        if (root->left->key > key) {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        }
        else if (root->left->key < key) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right != nullptr)
                root->left = leftRotate(root->left);
        }
        return (root->left == nullptr) ? root : rightRotate(root);
    }
    else {
        if (root->right == nullptr)
            return root;
        if (root->right->key > key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left != nullptr)
                root->right = rightRotate(root->right);
        }
        else if (root->right->key < key) {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }
        return (root->right == nullptr) ? root : leftRotate(root);
    }
}

Node* insert(Node* root, int key) {
    if (root == nullptr)
        return newNode(key);

    root = splay(root, key);

    if (root->key == key)
        return root;

    Node* node = newNode(key);
    if (root->key > key) {
        node->right = root;
        node->left = root->left;
        root->left = nullptr;
    }
    else {
        node->left = root;
        node->right = root->right;
        root->right = nullptr;
    }
    return node;
}

void preOrder(Node* node) {
    if (node != nullptr) {
        cout << node->key << " ";
        preOrder(node->left);
        preOrder(node->right);
    }
}




#endif