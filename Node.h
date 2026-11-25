#ifndef NODE_H
#define NODE_H

#include <stddef.h>

template <class T>
struct Node {
    // Data fields
    T data; // Stores the value of the node
    Node<T>* next; // Stores a pointer to the next node in the list.

    // Constructor
    Node(const T&);
};

template <class T>
Node<T>::Node(const T& value) : data(value), next(NULL) {}

#endif // NODE_H