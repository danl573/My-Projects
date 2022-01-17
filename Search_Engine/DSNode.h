#ifndef INC_21F_FLIGHT_PLANNER_DSNODE_H
#define INC_21F_FLIGHT_PLANNER_DSNODE_H


template<typename T>
class DSNode {
private:
    DSNode<T>* next;
    DSNode<T>* prev;
    T data;

public:
    /**
     * Constructors
     */
    DSNode();
    DSNode(T data);

    ///gives DSList access to private data members of DSNode
    template<typename> friend class DSList;
};

template<typename T>
DSNode<T>::DSNode(){
    next = prev = nullptr;
}

template<typename T>
DSNode<T>::DSNode(T data) {
    next = prev = nullptr;
    this->data = data;
}


#endif //INC_21F_FLIGHT_PLANNER_DSNODE_H
