#ifndef AlGORITHMS_H
#define AlGORITHMS_H

#include "Node.h"

#include <iostream>
#include <stdexcept>

using namespace std;

template <class T>
class Algorithms {
public:
    static bool is_circular(Node<T>*);
    static T find_middle(Node<T>*);
    static void print_list(Node<T>*);
    static void insert_front(Node<T>*&, const T&);
    static void insert_back(Node<T>*&, const T&);
    static void pop_front(Node<T>*&);
    static void pop_back(Node<T>*&);
    static void remove_first_occurrence(Node<T>*&, const T&);
    static void remove_last_occurrence(Node<T>*&, const T&);
};

/** Finds the middle element of a singly linked list.
    @param head: a pointer to head of the linked list.
    @return: the middle element of the list.
 */
template <class T>
T Algorithms<T>::find_middle(Node<T>* head) {
    if (!head) {
        throw out_of_range("List is empty");
    }

    bool is_even = true; // Flag to check if the number of nodes is even
    Node<T>* slow = head; // Slow pointer moves one step at a time
    Node<T>* fast = head; // Fast pointer moves two steps at a time

    while(fast && fast->next) {
        fast = fast->next;
        is_even = !is_even; // Toggle the even flag
        if (is_even) {
            slow = slow->next; // Move slow pointer only on even iterations
        }
    }
    return slow->data;
}

/** Checks if a singly linked list is circular.
    @param head: a pointer to head of the linked list.
    @return: true if the list is circular, false otherwise.
 */
template <class T>
bool Algorithms<T>::is_circular(Node<T>* head) {
    if (!head) {
        return false;
    }

    Node<T>* slow = head; // Slow pointer moves one step at a time
    Node<T>* fast = head; // Fast pointer moves two steps at a time

    while(fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return true;
        }
    }
    return false;
} // Time complexity: O(n)

/** Prints the elements of a singly linked list.
    @param head: a pointer to head of the linked list.
 */
template <class T>
void Algorithms<T>::print_list(Node<T>* head) {
    Node<T>* current = head;

    cout << "[head -> ";
    while (current) {
        cout << current->data;
        if (current->next != nullptr) {
            cout << " -> ";
        }
        current = current->next;
    }
    cout << " <- tail]" << endl;
}

/** Inserts a new node at the front of the list.
    @param head: a reference to a pointer to the head of the list.
    @param data: the data to be inserted.
*/
template <class T>
void Algorithms<T>::insert_front(Node<T>*& head, const T& data) {
    Node<T>* new_node = new Node<T>(data);
    new_node->next = head;
    head = new_node;
}

/** Inserts a new node at the back of the list.
    @param head: a reference to a pointer to the head of the list.
    @param data: the data to be inserted.
*/
template <class T>
void Algorithms<T>::insert_back(Node<T>*& head, const T& data) {
    Node<T>* new_node = new Node<T>(data);
    if (!head) {
        head = new_node;
        return;
    }

    Node<T>* current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = new_node;
} // Time complexity: O(n)

/** Removes the front node of the list.
    @param head: a reference to a pointer to the head of the list.
*/
template <class T>
void Algorithms<T>::pop_front(Node<T>*& head) {
    if (!head) {
        throw out_of_range("List is empty");
    }

    Node<T>* to_be_deleted = head;
    head = head->next;
    delete to_be_deleted;
} // Time complexity: O(1)

/** Removes the back node of the list.
    @param head: a reference to a pointer to the head of the list.
*/
template <class T>
void Algorithms<T>::pop_back(Node<T>*& head) {
    if (!head) {
        throw out_of_range("List is empty");
    }

    if (!head->next) { // Only one node in the list
        delete head;
        head = nullptr;
        return;
    }

    Node<T>* current = head;
    while (current->next && current->next->next) {
        current = current->next;
    }
    delete current->next; // Delete the last node
    current->next = nullptr; // Update the second last node's next to nullptr
} // Time complexity: O(n)

/** Removes the first occurrence of a node with the specified data.
    @param head: a pointer to the head of the list.
    @param target: the target data to be removed.
*/
template <class T>
void Algorithms<T>::remove_first_occurrence(Node<T>*& head, const T& target) {
    
    // If list is empty
    if (!head) {
        throw out_of_range("List is empty");
    }

    // If the head node is target
    if (head->data == target) {
        pop_front(head);
        return;
    }

    // Find the node before the target
    Node<T>* current = head;
    while (current->next && current->next->data != target) {
        current = current->next;
    }

    // If target is not found
    if (!current->next) {
        throw invalid_argument("Target not found in the list");
    }

    // Remove the target node
    Node<T>* to_be_deleted = current->next;
    current->next = to_be_deleted->next;
    delete to_be_deleted;
} // Time complexity: O(n)


template <class T>
void Algorithms<T>::remove_last_occurrence(Node<T>*& head, const T& target) {
    if (!head) {
        throw out_of_range("List is empty");
    }

    Node<T>* current = head;
    Node<T>* last_occurrence = nullptr;
    Node<T>* last_occurrence_prev = nullptr;
    Node<T>* previous = nullptr;

    // Find the last occurrence of the target
    while (current) {
        if (current->data == target) {
            last_occurrence_prev = prev;
            last_occurrence = current;
        }
        prev = current;
        current = current->next;
    }

    // If the target was not found
    if (!last_occurrence) {
        throw invalid_argument("Target not found in the list");
    }

    if (!last_occurrence_prev) { // The last occurrence is the head
        pop_front(head);
        return;
    } else {
        last_occurrence_prev->next = last_occurrence->next;
        delete last_occurrence;
    }
} // Time complexity: O(n)

#endif // AlGORITHMS_H