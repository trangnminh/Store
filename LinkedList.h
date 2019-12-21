#ifndef STORE_LINKEDLIST_H
#define STORE_LINKEDLIST_H

#include <iostream>
#include <string>

using namespace std;

template <typename T>
struct node {
    T data;
    node<T> *next;
};

template <typename T>
class LinkedList {
protected:
    int _size;
    node<T> *head;
    node<T> *tail;

    // Saving last node got for quicker search
    node<T> *lastNodeGot;
    int lastIndexGot;

    // isCached should be set to false every time the list changes
    bool isCached;

    node<T>* getNode(int index);
    //node<T>* findEndOfSortedString(node<T> *p, int (*cmp) (T&, T&));

public:
    LinkedList();
    ~LinkedList();

    // Return current size of list
    virtual int size();
    // Add a T object at specified index, increment size
    //virtual bool insert(int index, T);
    // Add a T object at end of linked list, increment size
    virtual bool append(T);
    // Add a T object at start of linked list, increment size
    virtual bool unshift(T);
    // Set the object at index, with T, increment size
    virtual bool set(int index, T);
    // Remove object at index, if index not reachable return false, else decrement size
    virtual T remove(int index);
    // Remove tail
    virtual T pop();
    // Remove head
    virtual T shift();
    // Get object of desired index, return false if failed
    virtual T get(int index);
    // Clear entire array
    //virtual void clear();
    // Sort the list, given a comparison function
    //virtual void sort(int (*cmp) (T&, T&));
};

// Initialize linked list with dummy values
template <typename T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    tail = nullptr;
    _size = 0;

    lastNodeGot = head;
    lastIndexGot = 0;
    isCached = false;
}

// Clear nodes and free memory
template <typename T>
LinkedList<T>::~LinkedList() {
    node<T> *current = head;
    while (current != nullptr) {
        current = head;
        head = head->next;
        delete current;
    }
    tail = nullptr;
    _size = 0;
    isCached = false;
}

// Get object T of desired index
template <typename T>
node<T>* LinkedList<T>::getNode(int index) {
    int pos = 0;
    node<T>* current = head;

    // Check if desired node is right after the previous one
    if (isCached && lastIndexGot <= index) {
        pos = lastIndexGot;
        current = lastNodeGot;
    }
    // Traverse list for desired index
    while (pos < index && current) {
        current = current->next;
        pos++;
    }
    // Check if desired object is available at index
    if (pos == index) {
        isCached = true;
        lastIndexGot = index;
        lastNodeGot = current;
        return current;
    }
    return nullptr;   // Index not found
}

// Return size of list
template<typename T>
int LinkedList<T>::size(){
    return _size;
}

// Append object T at end of list
template <typename T>
bool LinkedList<T>::append(T _node) {
    auto *tmp = new node<T>();
    tmp->data = _node;
    tmp->next = nullptr;

    if (head) { // List not empty
        tail->next = tmp;
        tail = tmp;
    }
    else {  // List empty
        head = tmp;
        tail = tmp;
    }
    _size++;
    isCached = false;

    return true;
}

// Add object T to start of list
template <typename T>
bool LinkedList<T>::unshift(T _node) {
    if (_size == 0) {
        return append(_node);
    }
    auto *tmp = new node<T>();
    tmp->next = head;
    tmp->data = _node;
    head = tmp;

    _size++;
    isCached = false;

    return true;
}

// Set object T at specified index
template <typename T>
bool LinkedList<T>::set(int index, T _node) {
    // Check if index position in bounds
    if (index < 0 || index >= _size) {
        return false;
    }
    getNode(index)->data = _node;
    return true;
}

// Pop last object off list
template <typename T>
T LinkedList<T>::pop() {
    if (_size <= 0) {
        return T();
    }
    isCached = false;

    if (_size >= 2) {
        node<T> *tmp = getNode(_size - 2);
        T ret = tmp->next->data;
        delete (tmp->next);
        tmp->next = nullptr;
        tail = tmp;
        _size--;
        return ret;
    } else {
        // Only one element left
        T ret = head->data;
        delete (head);
        head = nullptr;
        tail = nullptr;
        _size = 0;
        return ret;
    }
}

// Pop first object off list
template <typename T>
T LinkedList<T>::shift() {
    if (_size <= 0) {
        return T();
    }
    if (_size > 1) {
        node<T> *_next = head->next;
        T ret = head->data;
        delete (head);
        head = _next;
        _size--;
        isCached = false;
        return ret;
    } else {
        return pop();
    }
}

// Remove object T of specified index
template <typename T>
T LinkedList<T>::remove(int index) {
    if (index < 0 || index >= _size)
        return T();
    if (index == 0)
        return shift();
    if (index == _size - 1)
        return pop();

    node<T> *tmp = getNode(index - 1);
    node<T> *toDelete = tmp->next;
    T ret = toDelete->data;
    tmp->next = tmp->next->next;
    delete (toDelete);
    _size--;
    isCached = false;
    return ret;
}

// Get object T of specified index
template <typename T>
T LinkedList<T>::get(int index) {
    node<T> *tmp = getNode(index);
    return (tmp ? tmp->data : T());
}

//// Insert object T at specified index
//template <typename T>
//bool LinkedList<T>::insert(int index, T _node) {
//    if (index >= _size) {
//        return append(_node);
//    }
//    if (index == 0) {
//        return unshift(_node);
//    }
//    // Relink associated nodes
//    node<T> *tmp = new node<T>(), *prev = getNode(index - 1);
//    tmp->data = _node;
//    tmp->next = prev->next;
//    prev->next = tmp;
//
//    _size++;
//    isCached = false;
//    return true;
//}
//
//// Clear list of all members (WILL NOT FREE/DELETE POINTERS AND CLASSES)
//template <typename T>
//void LinkedList<T>::clear() {
//    while (size() > 0)
//        shift();
//}


#endif //STORE_LINKEDLIST_H
