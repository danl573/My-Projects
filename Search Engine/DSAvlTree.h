#ifndef INC_21F_FINAL_PROJ_TEMPLATE_DSAVLTREE_H
#define INC_21F_FINAL_PROJ_TEMPLATE_DSAVLTREE_H

#include <iostream>
#include "DSList.h"
#include "DSAvlNode.h"

template <typename T>
class DSAvlTree {
private:
    DSAvlNode<T>* root;
    int size;

    void insert(DSAvlNode<T>*&, int);
    bool contains(DSAvlNode<T>*&, int);
    void preOrder(DSAvlNode<T>*);
    void printInOrder(DSAvlNode<T>*);

    int height(DSAvlNode<T>* v);
    void balance(DSAvlNode<T>*&);
    void rotateWithLeftChild(DSAvlNode<T>*&);
    void doubleWithLeftChild(DSAvlNode<T>*&);
    void rotateWithRightChild(DSAvlNode<T>*&);
    void doubleWithRightChild(DSAvlNode<T>*&);

    //maybe create a generic postOrder function that takes a function parameter
    void PostOrDelete(DSAvlNode<T>*);
    void printTree(DSAvlNode<T>*, int);

public:
    DSAvlTree();
    ~DSAvlTree();
    DSAvlTree(const DSAvlTree<T>&);

    DSAvlTree<T>& operator=(const DSAvlTree<T>&);

    void insert(int);
    bool contains(int);
    void clear();

    void printTree();
    void printInOrder();


};

template <typename T>
DSAvlTree<T>::DSAvlTree() {
    root = nullptr;
    size = 0;
}

template<typename T>
DSAvlTree<T>::~DSAvlTree() {
    this->clear();
}

template<typename T>
DSAvlTree<T>::DSAvlTree(const DSAvlTree<T>& t) {
    *this = t;
}

template<typename T>
DSAvlTree<T>& DSAvlTree<T>::operator=(const DSAvlTree<T>& c){
    if(this != &c) {
        this->clear();
        preOrder(c.root);
    }
    return *this;
}

template<typename T>
void DSAvlTree<T>::insert(int val) {
    insert(root, val);
    size++;
}

template<typename T>
void DSAvlTree<T>::insert(DSAvlNode<T>*& c, int val) {
    if(c == nullptr)
        c = new DSAvlNode<T>(val);
    else if(val < c->data)
        insert(c->left, val);
    else if(c->data < val)
        insert(c->right, val);
    else
        ;
    balance(c);
}

template<typename T>
bool DSAvlTree<T>::contains(int val) {
    return contains(root, val);
}

template<typename T>
bool DSAvlTree<T>::contains(DSAvlNode<T>*& c, int val) {
    if (c == nullptr)
        return false;
    else if(c->data == val)
        return true;
    else if(val < c->data)
        return contains(c->left, val);
    else
        return contains(c->right, val);
}

template<typename T>
void DSAvlTree<T>::preOrder(DSAvlNode<T>* n) {
    if(n != nullptr) {
        this->insert(n->data);
        preOrder(n->left);
        preOrder(n->right);

    }
}

template<typename T>
void DSAvlTree<T>::printTree() {
    if(root == nullptr)
        return;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    //std::cout << "  AVLTREE IN ITS FULL BEAUTY:  " << std::endl;
    printTree(root, 0);
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

}

template<typename T>
void DSAvlTree<T>::printTree(DSAvlNode<T>* n, int sp) {
    if(n->right){
        printTree(n->right, sp+6);
        for(int i = 0; i < sp+3; i++)
            std::cout << " ";
        std::cout << "/";
    }
    std::cout << std::endl;
    for(int i = 0; i < sp; i++)
        std::cout << " ";
    std::cout << n->data << std::endl;

    if(n->left) {
        for(int i = 0; i < sp+3; i++)
            std::cout << " ";
        std::cout << "\\";
        printTree(n->left, sp+6);
    }

}

template<typename T>
void DSAvlTree<T>::printInOrder() {
    printInOrder(root);
    std::cout << std::endl;
}

template<typename T>
void DSAvlTree<T>::printInOrder(DSAvlNode<T>* n) {
    if(n != nullptr) {
        printInOrder(n->left);
        std::cout << n->data << ", ";
        printInOrder(n->right);
    }
}

template<typename T>
int DSAvlTree<T>::height(DSAvlNode<T> *v) {
    if(v == nullptr)
        return -1;
    v->height = std::max(height(v->left), height(v->right)) + 1;
    return v->height;
}

template<typename T>
void DSAvlTree<T>::balance(DSAvlNode<T>*& c) {
    if(c == nullptr)
        return;
    if(height(c->left) - height(c->right) > 1) {
        if(height(c->left->left) >= height(c->left->right))
            rotateWithLeftChild(c);
        else
            doubleWithLeftChild(c);
    } else if(height(c->right) - height(c->left) > 1) {
        if(height(c->right->right) >= height(c->right->left))
            rotateWithRightChild(c);
        else
            doubleWithRightChild(c);
    }

}

template<typename T>
void DSAvlTree<T>::rotateWithLeftChild(DSAvlNode<T>*& k2) {
    DSAvlNode<T>* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2 = k1;

}

template<typename T>
void DSAvlTree<T>::rotateWithRightChild(DSAvlNode<T>*& k1) {
    DSAvlNode<T>* k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1 = k2;
}

template<typename T>
void DSAvlTree<T>::doubleWithLeftChild(DSAvlNode<T>*& k3) {
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

template<typename T>
void DSAvlTree<T>::doubleWithRightChild(DSAvlNode<T>*& k1) {
    rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);
}

template<typename T>
void DSAvlTree<T>::clear() {
    PostOrDelete(root);
    root = nullptr;
}

template<typename T>
void DSAvlTree<T>::PostOrDelete(DSAvlNode<T>* n) {
    if(n != nullptr) {
        PostOrDelete(n->left);
        PostOrDelete(n->right);
        delete n;
    }

}




#endif //INC_21F_FINAL_PROJ_TEMPLATE_DSAVLTREE_H
