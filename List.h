//
// Created by minesk on 22/12/2019.
//

#ifndef UNTITLED_LIST_H
#define UNTITLED_LIST_H

#include <iostream>
#include <string>

using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T> *next;
};

template <typename T>
class List {
private:
    int size;
    Node<T> *head, *tail;
public:
    List() {
        size = 0;
        head = NULL;
        tail = NULL;
    }

    // Getters
    int getSize() {
        return this->size;
    }

    // Append a new node to end of list
    void append(T value) {
        auto *tmp = new Node<T>;
        tmp->data = value;
        tmp->next = NULL;

        // If list empty, appended node is head
        if (head == NULL) {
            head = tmp;
            tail = tmp;
        } else {
            tail->next = tmp;
            tail = tmp;
        }
        size++;
    }

    // Delete first node in list
    void deleteHead() {
        Node<T> *tmp;
        tmp = head;
        head = head->next;
        delete tmp;
        size--;
    }

    // Delete last node in list
    void deleteTail() {
        auto *current = head;
        auto *previous = new Node<T>;

        while (current->next != NULL) {
            previous = current;
            current = current->next;
        }
        tail = previous;
        previous->next = NULL;
        delete current;
        size--;
    }

    // Delete a node in a given position
    void deleteNode(int pos) {
        if (pos == 0) return deleteHead();
        if (pos == size - 1) return deleteTail();
        if (pos >= size) return;    // Out of scope

        auto *current = head;

        // Traverse list until the previous of targeted node
        for (int i = 0; current != NULL && i < pos - 1; i++) {
            current = current->next;
        }
        if (current == NULL || current->next == NULL) return;

        // Delete node at desired position (next of current)
        Node<T> *tmp = current->next->next; // Store node next to to-be-deleted note
        free (current->next);   // Free memory at targeted node
        current->next = tmp;    // Relink 2 nodes before and after deleted node
        size--; // Decrement size
    }

    // Return an object T at desired index, or null if not found
    T get(int index) {
        int pos = 0;

        // Start from head of list
        Node<T>* current = head;

        // Traverse list until desired index
        while (pos < index && current != NULL) {
            current = current->next;
            pos++;
        }

        // Check if there's an object at desirable index
        if (pos == index) {
            return (current ? current->data : NULL);
        }
        else {
            cout << "Index not found" << endl;
            return NULL;
        }
    }
};

#endif //UNTITLED_LIST_H
