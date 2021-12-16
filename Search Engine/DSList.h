#ifndef INC_21F_FLIGHT_PLANNER_DSLIST_H
#define INC_21F_FLIGHT_PLANNER_DSLIST_H

#include <exception>
#include <stdexcept>
#include "DSNode.h"

template<typename T>
class DSList {
private:
    DSNode<T> *head, *tail;
    int size;

public:
    /**
     * Constructors and Destructors
     */
    DSList();
    ~DSList();
    DSList(const DSList<T>&);

    /**
     *  Assignment operator
     */
    DSList<T>& operator=(const DSList<T>&);

    /**
     *  push_back function adds a given piece of data to the end of the list
     * @param data the node to add
     */
    void push_back(T data);

    /**
     *  push_front function adds a given piece of data to the front of the list
     * @param data the node to add
     */
    void push_front(T data);

    /**
     *  removes the last node from the list
     */
    void pop();

    /**
     *  Searches list to determine if given variable exists
     * @param obj data to find
     * @return true if obj if found in list, false otherwise
     */
    bool contains(T obj);

    /**
     *  clear will totally delete all the nodes in the list
     */
    void clear();

    /**
     *  front will return the head node data
     * @return the head node data
     */
    T& front();

    /**
     *  back will return the tail node data
     * @return tail node data
     */
    T& back();

    /**
     *  isEmpty will return if list if empty
     * @return true if list is empty
     *         false otherwise
     */
    bool isEmpty();

    /**
     *  getSize will return the size of the list
     * @return size of list
     */
    int getSize();




    ///Iterator class and methods
    //sorry if this is weird, i didnt really know how to format nested classes
    class Iterator {
        friend class DSList;
    private:
        DSNode<T>* curr;
        Iterator(DSNode<T>* p) : curr(p) {};
    public:
        /**
         * Constructors and operator methods
         */
        Iterator() : curr(nullptr) {}

        /**
         *  equivalence and non-equivalence operators, compares nodes
         */
        bool operator!=(const Iterator itr) const {
            return curr != itr.curr;
        }
        bool operator==(const Iterator itr) const {
            return curr == itr.curr;
        }

        /**
         *  dereference operator, returns data in iterator
         * @return
         */
        T& operator*() {
            return curr->data;
        }

        /**
         *  Increment operator, moves iterator up by one
         * @return incremented iterator
         */
        Iterator& operator++() {
            if(curr)
                curr = curr->next;
            return *this;
        }

        /**
         *  Decrement operator, moves iterator down by one
         * @return decremented iterator
         */
        Iterator& operator--() {
            if(curr)
                curr = curr->prev;
            return *this;
        }

        /**
         *  ifNull will return whether the current iterator is pointing to nullptr
         * @return true if curr is nullptr
         */
        bool ifNull() {
            return curr == nullptr;
        }
    };

    /**
     *  returns the head of the list as an iterator
     *  @return iterator pointing to head
     */
    Iterator begin() const {return Iterator(head);}

    /**
     *  returns the tail of the list as an iterator
     * @return iterator pointing to tail
     */
    Iterator end() const {return Iterator(tail);}

    /**
     *  Inserts a node after the iterator node, returns inserted node
     * @param pos iterator to where node will be inserted
     * @param val data to be inserted
     * @return iterator to inserted node
     */
    Iterator insert(Iterator pos, const T& val) {
        auto* newNode = new DSNode<T>(val);

        if(!head) {
            head = tail = pos.curr;
            return Iterator(newNode);
        }

        if(pos.curr->next) {
            newNode->next = pos.curr->next;
            pos.curr->next->prev = newNode;
        }
        pos.curr->next = newNode;
        newNode->prev = pos.curr;

        if(tail == pos.curr)
            tail = newNode;

        size++;
        return Iterator(newNode);
    }

    /**
     *  Removes node that the iterator is pointing to
     * @param pos node to be removed
     */
    void remove(Iterator pos) {
        DSNode<T>* deadNode = pos.curr;
        if(deadNode->next && head != deadNode)
            deadNode->prev->next = deadNode->next;
        if(deadNode->prev && tail != deadNode)
            deadNode->next->prev = deadNode->prev;

        if(head == deadNode && tail == deadNode){
            head = tail = nullptr;
        } else if(head == deadNode) {
            head = deadNode->next;
            deadNode->next->prev = nullptr;
        } else if(tail == deadNode) {
            tail = deadNode->prev;
            deadNode->prev->next = nullptr;
        }
        delete deadNode;
        size--;
    }



    /**
     *  returns iterator to a the first instance of a obj
     * @param obj data to be found
     * @return iterator to node of data, iterator to head if not found
     */
    Iterator find(T obj) {
        DSNode<T>* temp = head;
        bool ifContains = false;
        while(!ifContains || temp == nullptr) {
            if(temp->data == obj) {
                ifContains = true;
            } else
                temp = temp->next;
        }
        return Iterator(temp);
    }
};



template<typename T>
DSList<T>::DSList() {
    head = tail = nullptr;
    size = 0;
}

template<typename T>
DSList<T>::~DSList() {
    DSNode<T>* temp = head;
    while(head) {
        head = head->next;
        delete temp;
        temp = head;
    }
}

template<typename T>
DSList<T>::DSList(const DSList<T>& copyList) {
    if(copyList.head == nullptr) {
        head = tail = nullptr;
        size = 0;
    } else {
        DSNode<T>* currCopy = copyList.head;
        auto* curr = new DSNode<T>(currCopy->data);
        head = tail = curr;
        size = copyList.size;

        while(currCopy->next) {
            currCopy = currCopy->next;
            curr = new DSNode<T>(currCopy->data);
            tail->next = curr;
            curr->prev = tail;
            tail = curr;
        }
    }
}

template<typename T>
DSList<T>& DSList<T>::operator=(const DSList<T> &copyList) {
    clear();

    if(copyList.head == nullptr) {
        head = tail = nullptr;
        size = 0;
    } else {
        DSNode<T>* currCopy = copyList.head;
        auto* curr = new DSNode<T>(currCopy->data);
        head = tail = curr;
        size = copyList.size;

        while(currCopy->next) {
            currCopy = currCopy->next;
            curr = new DSNode<T>(currCopy->data);
            tail->next = curr;
            curr->prev = tail;
            tail = curr;
        }
    }

    return *this;
}

template<typename T>
void DSList<T>::push_back(T data) {
    auto* newNode = new DSNode<T>(data);
    if(head == nullptr)
        head = newNode;
    if(tail != nullptr)
        tail->next = newNode;

    newNode->prev = tail;
    tail = newNode;
    size++;
}

template<typename T>
void DSList<T>::push_front(T data) {
    auto* newNode = new DSNode<T>(data);
    if(tail == nullptr)
        tail = newNode;
    if(head != nullptr)
        head->prev = newNode;

    newNode->next = head;
    head = newNode;
    size++;
}

template<typename T>
void DSList<T>::pop() {
    DSNode<T>* temp = tail;

    if(head == tail) {
        head = tail = nullptr;
    } else {
        tail = temp->prev;
        tail->next = nullptr;
    }
    delete temp;

}

template<typename T>
bool DSList<T>::contains(T obj) {
    DSNode<T>* temp = head;
    bool ifContains = false;
    while(temp != nullptr) {
        if(temp->data == obj)
            ifContains = true;
        temp = temp->next;
    }
    return ifContains;
}

template<typename T>
void DSList<T>::clear() {
    DSNode<T>* temp = head;
    while(head) {
        head = head->next;
        delete temp;
        temp = head;
    }
    head = tail = nullptr;
    size = 0;
}

template<typename T>
T& DSList<T>::front() {
    if(!head)
        throw std::out_of_range("cant return empty list");
    return head->data;
}

template<typename T>
T& DSList<T>::back() {
    if(!tail)
        throw std::out_of_range("cant return empty list");
    return tail->data;
}

template<typename T>
bool DSList<T>::isEmpty() {
    return (head == nullptr);
}

template<typename T>
int DSList<T>::getSize() {
    return size;
}




#endif //INC_21F_FLIGHT_PLANNER_DSLIST_H
