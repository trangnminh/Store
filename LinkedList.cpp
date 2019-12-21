#include "LinkedList.h"

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

// Insert object T at specified index
template <typename T>
bool LinkedList<T>::insert(int index, T _node) {
    if (index >= _size) {
        return append(_node);
    }
    if (index == 0) {
        return unshift(_node);
    }
    // Relink associated nodes
    node<T> *tmp = new node<T>(), *prev = getNode(index - 1);
    tmp->data = _node;
    tmp->next = prev->next;
    prev->next = tmp;

    _size++;
    isCached = false;
    return true;
}

// Append object T at specified index
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

// Clear list of all members (WILL NOT FREE/DELETE POINTERS AND CLASSES)
template <typename T>
void LinkedList<T>::clear() {
    while (size() > 0)
        shift();
}

