#ifndef INC_21F_FINAL_PROJ_TEMPLATE_DSAVLNODE_H
#define INC_21F_FINAL_PROJ_TEMPLATE_DSAVLNODE_H



template <typename T>
class DSAvlNode {
private:
    DSAvlNode* left;
    DSAvlNode* right;
    T data;
    int height;

    template <typename> friend class DSAvlTree;

public:
    DSAvlNode();
    DSAvlNode(T, int = 0, DSAvlNode<T>* = nullptr, DSAvlNode<T>* = nullptr);

};

template <typename T>
DSAvlNode<T>::DSAvlNode() {
    left = right = nullptr;
    height = 0;
}

template <typename T>
DSAvlNode<T>::DSAvlNode(T d, int h, DSAvlNode<T>* l, DSAvlNode<T>* r) {
    data = d;
    left = l;
    right = r;
    height = h;
}

#endif //INC_21F_FINAL_PROJ_TEMPLATE_DSAVLNODE_H
