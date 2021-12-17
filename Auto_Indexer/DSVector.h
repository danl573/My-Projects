#ifndef INC_21F_PA02_DSVECTOR_H
#define INC_21F_PA02_DSVECTOR_H


#include <iostream>
#include <exception>

template<typename T>
class DSVector {
private:
    T* data;

    //size = how many elements inserted
    int size;

    //capacity = how much space available
    int capacity;

    /**
     *  grow function resizes the vector with a larger capacity
     *  by allocating a new array with a larger size and copying
     *  the elements onto it
     */
    void grow();

public:
    /**
     *  Constructors and Destructor
     */
    DSVector();
    DSVector(int cap);
    DSVector(const DSVector<T>& vec);
    ~DSVector();

    /**
     *  Overloaded Assignment operator
     */
    DSVector<T>& operator=(const DSVector& vec);


    ///SIZE AND CAPACITY

    /**
     *  Returns the amount of space available in the vector for
     *  elements
     * @return the capacity of the vector
     */
    int getCapacity();

    /**
     *  Returns the amount of elements inserted into the vector
     * @return the size of the vector
     */
    int getSize();

    /**
     *  Returns whether or not the vector is currently empty
     * @return true if vector is empty, false otherwise
     */
    bool ifEmpty();


    ///ELEMENT ACCESS

    /**
     *  Subscript operator and at() method to access a particular
     *  element in the vector
     * @return The element requested by reference
     */
    T& operator[](int loc);
    T& at(int loc);

    /**
     *  Method to access the first element in the array, throws
     *  exception if vector is empty
     * @return The first element by reference
     */
    T& front();

    /**
     * Method to access the last element of the array, throws
     * exception if vector is empty
     * @return The last element by reference
     */
    T& back();


    ///MODIFIERS

    /**
     *  Adds an element to the end of the vector
     *  @param element object to add
     */
    void push_back(const T& element);

    /**
     *  Removes the last element of the vector
     */
    void pop_back();

    /**
     *  Inserts an element to the vector at a
     *  given index
     *  @param element object to insert
     *  @param index location of insertion
     */
    void insert(const T& element, int index);

    /**
     *  Removes an element from the vector at a given
     *  index
     *  @param loc the index of the element to remove
     */
    void removeIndex(int loc);

    /**
     *  Removes the first instant of an  element
     *  from the vector given the object
     * @return true if element was successfully removed
     *          false otherwise
     * @param obj object to be deleted from vector
     */
    bool removeObject(const T& obj);

    /**
     *  Deletes all the elements in the array, keeps current capacity
     */
    void clear();

    /**
     *  uses std::sort to sort the vector from least to greatest (uses < operator)
     */
    void sort();

    /**
     *  Swaps two elements in the vector given both of their indices
     *  @param loc1 index of the first element to be swapped
     *  @param loc2 inded of the second element
     */
    void swap(int loc1, int loc2);

    /**
     *  Searches the vector for a specific element and returns the index
     * @return index of the element if found
     *          -1 if element if not found
     * @param element object to be found
     */
    int find(const T& element);
};

template<typename T>
DSVector<T>::DSVector() {
    data = new T[10];
    size = 0;
    capacity = 10;
}

template<typename T>
DSVector<T>::DSVector(int cap) {
    //Throws exception if capacity is less than zero
    if(cap < 0)
        throw std::out_of_range("Bad index value");
    capacity = cap;
    data = new T[cap];
    size = 0;
}

template<typename T>
DSVector<T>::DSVector(const DSVector<T>& vec) {
    data = new T[vec.capacity];
    size = vec.size;
    capacity = vec.capacity;

    //copy elements
    for(int i = 0; i < vec.capacity; i++)
        data[i] = vec.data[i];
}

template<typename T>
DSVector<T>::~DSVector() {
    delete[] data;
}

template<typename T>
DSVector<T>& DSVector<T>::operator=(const DSVector& vec) {
    size = vec.size;
    capacity = vec.capacity;
    delete[] data;
    data = new T[vec.capacity];

    //copy elements
    for(int i = 0; i < vec.capacity; i++)
        data[i] = vec.data[i];
    return *this;
}

template<typename T>
int DSVector<T>::getCapacity() {
    return capacity;
}

template<typename T>
int DSVector<T>::getSize() {
    return size;
}

template<typename T>
bool DSVector<T>::ifEmpty() {
    return (size == 0);
}

template<typename T>
T& DSVector<T>::operator[](int loc) {
    //throws exception if index is out of range
    if(loc < 0 || loc > capacity)
        throw std::out_of_range("bad index value");
    return data[loc];
}

template<typename T>
T& DSVector<T>::at(int loc) {
    //throws exception if index is out of range
    if(loc < 0 || loc > capacity)
        throw std::out_of_range("bad index value");
    return data[loc];
}

template<typename T>
T& DSVector<T>::front() {
    //throws exception if vector is empty
    if(size < 1)
        throw std::out_of_range("cant return empty array");
    return data[0];
}

template<typename T>
T& DSVector<T>::back() {
    //throws exception if vector is empty
    if(size < 1)
        throw std::out_of_range("can't return empty array");
    return data[size - 1];
}

template<typename T>
void DSVector<T>::push_back(const T& element) {
    //checks capacity, increases capacity if needed
    if(size == capacity)
        grow();
    data[size] = element;
    size++;
}

template<typename T>
void DSVector<T>::pop_back() {
    //throws exception if vector is empty
    if(size == 0)
        throw std::out_of_range("can't pop empty array");

    //deletes last element (bc apparently size-- alone isn't good enough)
    T* temp = new T[capacity];
    size--;
    for(int i = 0; i < size; i++)
        temp[i] = data[i];
    delete[] data;
    data = temp;
}

template<typename T>
void DSVector<T>::insert(const T& element, int index) {
    //throws exception if index is outside vector
    if(index < 0 || index > size)
        throw std::out_of_range("bad index value");
    if(size == capacity)
        grow();

    //adds new element by shifting all elements after by one
    T temp1 = element;
    T temp2;
    for(int j = index; j <= size; j++) {
        temp2 = data[j];
        data[j] = temp1;
        temp1 = temp2;
    }
    size++;
}

template<typename T>
void DSVector<T>::removeIndex(int loc) {
    //throws exception if index out of vector range
    if(loc < 0 || loc > size)
        throw std::out_of_range("bad index value");

    //copy all elements except to removed one to a new array
    T* temp = new T[capacity];
    size--;
    for(int i = 0, j = 0; j < size; i++, j++) {
        if (loc == i)
            j--;
        else
            temp[j] = data[i];
    }
    delete[] data;
    data = temp;
}

template<typename T>
bool DSVector<T>::removeObject(const T& obj) {
    //searches for element index
    int index = -1;
    for(int i = 0; i < size; i++) {
        if(data[i] == obj) {
            index = i;
            break;
        }
    }

    //calls removeIndex() if element is found
    if(index == -1)
        return false;
    removeIndex(index);
    return true;
}

template<typename T>
void DSVector<T>::clear() {
    delete[] data;
    data = new T[capacity];
    size = 0;
}

template<typename T>
void DSVector<T>::sort() {
    std::sort(data, data + size);
}

template<typename T>
void DSVector<T>::swap(int loc1, int loc2) {
    //Throws exception if either index is outside vector
    if(loc1 < 0 || loc2 < 0 || loc1 > size || loc2 > size)
        throw std::out_of_range("bad index value");

    T temp = data[loc1];
    data[loc1] = data[loc2];
    data[loc2] = temp;
}

template<typename T>
void DSVector<T>::grow() {
    if(capacity == 0)
        capacity = 10;
    else
        capacity *= 2;

    T* temp = new T[capacity];
    for(int i = 0; i < size; i++)
        temp[i] = data[i];

    delete[] data;
    data = temp;
}

template<typename T>
int DSVector<T>::find(const T& element) {
    for(int i = 0; i < size; i++)
        if(element == data[i])
            return i;
    return -1;
}

#endif //INC_21F_PA02_DSVECTOR_H
