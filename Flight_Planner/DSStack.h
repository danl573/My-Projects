#ifndef INC_21F_FLIGHT_PLANNER_DSSTACK_H
#define INC_21F_FLIGHT_PLANNER_DSSTACK_H

#include "DSList.h"

template<typename T>
class DSStack {
private:
    DSList<T> stack;

public:
    /**
     *  Default constructor
     */
    DSStack() = default;

    /**
     *  isEmpty returns if the stack is empty
     * @return true if stack is empty, false otherwise
     */
    bool isEmpty();

    /**
     *  adds data to the top of the stack
     *  @param data to add
     */
    void push(const T&);

    /**
     *  removes the top most node from the stack
     */
    void pop();

    /**
     *  returns the data at the top of the stack
     * @return top of the stack
     */
    T top();

    /**
     * clears the stack of data
     */
    void clear();

};

template<typename T>
bool DSStack<T>::isEmpty() {
    return stack.isEmpty();
}

template<typename T>
void DSStack<T>::push(const T& data) {
    stack.push_back(data);
}

template<typename T>
void DSStack<T>::pop() {
    stack.pop();
}

template<typename T>
T DSStack<T>::top() {
    return stack.back();
}

template<typename T>
void DSStack<T>::clear() {
    stack.clear();
}


#endif //INC_21F_FLIGHT_PLANNER_DSSTACK_H
