#ifndef SPLAYTREE_H
#define SPLAYTREE_H
#include "BaseLibrariesFile.h"
// first draft of splaytree implementation

// make splaying tree:
// it is almost like AVL,
// but the difference is that every time a ST_Node is accessed,
// it is made root, and the rest of the elements are balanced according to the new root in such a manner that this tree also acts as a BST
// add a bool access variable to the ST_Nodes so a record of last accessed ST_Node can be kept and made into root
// and for proper funcionality
// take 2 trees where every new root becomes root of new tree while the old is 
//popped onto the new one and deleted, kind of like using 2 queues for 
//making 1 stack question from DSA lab sessional
// and also make a function to check if the tree is empty
// and also make a function to check if the tree is balanced

template <class T = int>
struct ST_Node {
    T data;
    ST_Node *left, *right;
    bool last_accessed = false;
    
    ST_Node() {
        this->data = T();
        this->left = nullptr;
        this->right = nullptr;
    } 
    ST_Node(const T& data1) {
        this->data = data1;
        this->left = nullptr;
        this->right = nullptr;
    }
};

template <class T = int>
struct STree {

    ST_Node<T>* root;

    STree() {
    this->root = nullptr;
}
    // Destructor
    ~STree() {
        clear(root);
    }

    // Basic operations
    void insert(const T& data) { root = insert(root, data); }
    bool search(const T& data) { root = splay(root, data); return (root != nullptr && root->data == data); }
    void remove(const T& data) { root = remove(root, data); }
    void preOrder() const { preOrder(root); cout << endl; }
    void clear() { clear(root); root = nullptr; }

private:
    // Helper functions
    ST_Node<T>* rightRotate(ST_Node<T>* x) {
        ST_Node<T>* y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }

    ST_Node<T>* leftRotate(ST_Node<T>* x) {
        ST_Node<T>* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }

    ST_Node<T>* splay(ST_Node<T>* root, const T& data) {
        if (root == nullptr || root->data == data)
            return root;

        if (root->data > data) {
            if (root->left == nullptr) return root;
            
            if (root->left->data > data) {
                // Zig-Zig (right-right)
                root->left->left = splay(root->left->left, data);
                root = rightRotate(root);
            }
            else if (root->left->data < data) {
                // Zig-Zag (right-left)
                root->left->right = splay(root->left->right, data);
                if (root->left->right != nullptr)
                    root->left = leftRotate(root->left);
            }
            return (root->left == nullptr) ? root : rightRotate(root);
        }
        else {
            if (root->right == nullptr) return root;
            
            if (root->right->data > data) {
                // Zag-Zig (left-right)
                root->right->left = splay(root->right->left, data);
                if (root->right->left != nullptr)
                    root->right = rightRotate(root->right);
            }
            else if (root->right->data < data) {
                // Zag-Zag (left-left)
                root->right->right = splay(root->right->right, data);
                root = leftRotate(root);
            }
            return (root->right == nullptr) ? root : leftRotate(root);
        }
    }

    ST_Node<T>* insert(ST_Node<T>* root, const T& data) {
        if (root == nullptr)
            return new ST_Node<T>(data);

        root = splay(root, data);

        if (root->data == data)
            return root;

        ST_Node<T>* newNode = new ST_Node<T>(data);
        if (root->data > data) {
            newNode->right = root;
            newNode->left = root->left;
            root->left = nullptr;
        }
        else {
            newNode->left = root;
            newNode->right = root->right;
            root->right = nullptr;
        }
        return newNode;
    }

    ST_Node<T>* remove(ST_Node<T>* root, const T& data) {
        if (root == nullptr) return nullptr;

        root = splay(root, data);

        if (root->data != data)
            return root;

        ST_Node<T>* temp;
        if (root->left == nullptr) {
            temp = root;
            root = root->right;
        }
        else {
            temp = root;
            root = splay(root->left, data);
            root->right = temp->right;
        }
        delete temp;
        return root;
    }

    void preOrder(ST_Node<T>* node) const {
        if (node != nullptr) {
            cout << node->data << " ";
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    void clear(ST_Node<T>* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }
    bool isEmpty() const {
        return root == nullptr;
    }
    bool isBalanced() const {
        return isBalanced(root);
    }
};

#endif