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
    node<T>* findEndOfSortedString(node<T> *p, int (*cmp) (T&, T&));

public:
    LinkedList();
    ~LinkedList();

    // Return current size of list
    virtual int size();
    // Add a T object at specified index, increment size
    virtual bool insert(int index, T);
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
    virtual void clear();
    // Sort the list, given a comparison function
    //virtual void sort(int (*cmp) (T&, T&));
};

#endif //STORE_LINKEDLIST_H
