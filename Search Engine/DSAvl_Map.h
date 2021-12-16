#ifndef INC_21F_FINAL_PROJ_TEMPLATE_DSAVL_MAP_H
#define INC_21F_FINAL_PROJ_TEMPLATE_DSAVL_MAP_H

#include <functional>
#include <iostream>
#include <exception>

template <typename K, typename V>
class DSAvl_Map {
private:
    class Element {
    public:
        Element* left;
        Element* right;
        K key;
        V value;
        int height;
        Element(){
            left = right = nullptr;
            height = 0;
        }
        Element(K userKey, Element* l = nullptr, Element* r = nullptr, int h = 0) {
            key = userKey;
            left = l;
            right = r;
            height = h;
        }
    };
    Element* root;
    int num_nodes;
    int num_calls_to_insert;




    V& insert(Element*&, K&);
    bool contains(Element*&, K);
    V& getValue(Element*&, const K&);

    void preOrder(Element*);
    void preOrder(Element*, std::function<void(int,int)>, int, int);
    void printInOrder(Element*);
    void copyToVector(Element*, std::vector<std::pair<K,V>>&);

    int height(Element*);
    void balance(Element*&);
    void rotateWithLeftChild(Element*&);
    void doubleWithLeftChild(Element*&);
    void rotateWithRightChild(Element*&);
    void doubleWithRightChild(Element*&);

    void PostOrDelete(Element*);
    void printTree(Element*, int);

public:
    DSAvl_Map();
    ~DSAvl_Map();
    DSAvl_Map(const DSAvl_Map<K,V>&);

    DSAvl_Map<K,V>& operator=(const DSAvl_Map<K,V>&);

    int get_num_nodes() { return num_nodes;}
    int get_num_insert_calls() {return num_calls_to_insert;}
    void copyToVector(std::vector<std::pair<K,V>>&);

    void preOrder(std::function<void(int,int)>, int, int);

    V& insert(K);
    bool contains(K);
    void clear();
    V& getValue(const K&);

    void printTree();
    void printInOrder();

};

template<typename K, typename V>
DSAvl_Map<K, V>::DSAvl_Map() {
    root = nullptr;
    num_nodes = 0;
    num_calls_to_insert = 0;
}

template<typename K, typename V>
DSAvl_Map<K,V>::~DSAvl_Map() {
    this->clear();
}

template<typename K, typename V>
DSAvl_Map<K,V>::DSAvl_Map(const DSAvl_Map<K,V>& t) {
    *this = t;
}

template<typename K, typename V>
DSAvl_Map<K,V>& DSAvl_Map<K,V>::operator=(const DSAvl_Map<K,V>& arg) {
    if(this != arg) {
        this->clear();
        preOrder(arg.root);
    }
    return *this;
}

template<typename K, typename V>
V& DSAvl_Map<K, V>::insert(K key) {
    return insert(root, key);

}

template<typename K, typename V>
V& DSAvl_Map<K, V>::insert(DSAvl_Map::Element*& c, K& key) {
    num_calls_to_insert++;
    if (c == nullptr) {
        c = new Element(key);
        num_nodes++;
        balance(c);
        return c->value;
    } else if (key < c->key) {
        V& temp = insert(c->left, key);
        balance(c);
        return temp;
    } else if (c->key < key) {
        V& temp = insert(c->right, key);
        balance(c);
        return temp;
    } else
        ;
    balance(c);
    return c->value;
}

template<typename K, typename V>
bool DSAvl_Map<K, V>::contains(K key) {
    return contains(root, key);
}

template<typename K, typename V>
bool DSAvl_Map<K, V>::contains(DSAvl_Map::Element*& c, K key) {
    if (c == nullptr)
        return false;
    else if(c->key == key)
        return true;
    else if(key < c->key)
        return contains(c->left, key);
    else
        return contains(c->right, key);
}

template<typename K, typename V>
void DSAvl_Map<K, V>::clear() {
    PostOrDelete(root);
    root = nullptr;
    num_nodes = 0;
    num_calls_to_insert = 0;
}

template<typename K, typename V>
void DSAvl_Map<K,V>::printTree() {
    if(root == nullptr)
        return;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    //std::cout << "  AVLTREE IN ITS FULL BEAUTY:  " << std::endl;
    printTree(root, 0);
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
}

template<typename K, typename V>
void DSAvl_Map<K, V>::printTree(DSAvl_Map::Element* n, int sp) {
    if(n->right) {
        printTree(n->right, sp + 3);
//        for (int i = 0; i < sp + 5; i++)
//            std::cout << " ";
//        std::cout << "/";
    }
    std::cout << std::endl;
    for (int i = 0; i < sp; i++)
        std::cout << " ";
    std::cout << n->key << std::endl;

    if (n->left) {
//        for (int i = 0; i < sp + 5; i++)
//            std::cout << " ";
//        std::cout << "\\";
        printTree(n->left, sp + 3);
    }
}

template<typename K, typename V>
void DSAvl_Map<K, V>::printInOrder() {
    printInOrder(root);
    std::cout << std::endl;
}

template<typename K, typename V>
void DSAvl_Map<K, V>::printInOrder(DSAvl_Map::Element* n) {
    if(n != nullptr) {
        printInOrder(n->left);
        std::cout << n->key << ", ";
        printInOrder(n->right);
    }
}

template<typename K, typename V>
void DSAvl_Map<K, V>::copyToVector(DSAvl_Map::Element* n, std::vector<std::pair<K, V>>& set) {
    if(n != nullptr) {
        set.push_back(std::pair<K,V>(n->key, n->value));
        copyToVector(n->left, set);
        copyToVector(n->right, set);
    }

}

template<typename K, typename V>
void DSAvl_Map<K, V>::copyToVector(std::vector<std::pair<K, V>> &set) {
    copyToVector(root, set);
}

template<typename K, typename V>
void DSAvl_Map<K, V>::preOrder(DSAvl_Map::Element* n) {
    if(n != nullptr) {
        this->insert(n->key);
        preOrder(n->left);
        preOrder(n->right);
    }
}

template<typename K, typename V>
void DSAvl_Map<K, V>::preOrder(DSAvl_Map::Element* n, std::function<void(int,int)> func, int x, int y) {
    if(n != nullptr) {
        func(x,y);
        preOrder(n->left);
        preOrder(n->right);
    }
}

template<typename K, typename V>
void DSAvl_Map<K, V>::PostOrDelete(DSAvl_Map::Element* n) {
    if(n != nullptr) {
        PostOrDelete(n->left);
        PostOrDelete(n->right);
        delete n;
    }
}

template<typename K, typename V>
int DSAvl_Map<K, V>::height(DSAvl_Map::Element* v) {
    if(v == nullptr)
        return -1;
    return v->height;
}

template<typename K, typename V>
void DSAvl_Map<K, V>::balance(DSAvl_Map::Element*& c) {
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

template<typename K, typename V>
void DSAvl_Map<K, V>::rotateWithLeftChild(DSAvl_Map::Element*& k2) {
    Element* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = std::max(height(k2->left), height(k2->right))+1;
    k1->height = std::max(height(k1->left), height(k1->right))+1;
    k2 = k1;
}

template<typename K, typename V>
void DSAvl_Map<K, V>::doubleWithLeftChild(DSAvl_Map::Element*& k3) {
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

template<typename K, typename V>
void DSAvl_Map<K, V>::rotateWithRightChild(DSAvl_Map::Element*& k1) {
    Element* k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k2->height = std::max(height(k2->left), height(k2->right))+1;
    k1->height = std::max(height(k1->left), height(k1->right))+1;
    k1 = k2;
}

template<typename K, typename V>
void DSAvl_Map<K, V>::doubleWithRightChild(DSAvl_Map::Element*& k1) {
    rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);
}

template<typename K, typename V>
V& DSAvl_Map<K, V>::getValue(const K& key) {
    return getValue(root, key);
}

template<typename K, typename V>
V &DSAvl_Map<K, V>::getValue(DSAvl_Map::Element*& c, const K& key) {
    if (c == nullptr)
        throw std::runtime_error("Item Not Found");
    else if(c->key == key)
        return c->value;
    else if(key < c->key)
        return getValue(c->left, key);
    else
        return getValue(c->right, key);
}



#endif //INC_21F_FINAL_PROJ_TEMPLATE_DSAVL_MAP_H
