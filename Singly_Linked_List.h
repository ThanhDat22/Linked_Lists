#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <iostream>
#include <cstddef>
#include <stdexcept>

using namespace std;

template <class T>
class Singly_Linked_List {
public:
    // Constructors
    Singly_Linked_List(); // Default constructor
    Singly_Linked_List(const Singly_Linked_List<T>&); // Copy constructor

    // Destructor: release the dynamically allocated memory
    virtual ~Singly_Linked_List();

    // Operator
    const Singly_Linked_List<T>& operator=(const Singly_Linked_List<T>&); // Deep-copy assignment operator

    template <class E>
    friend ostream& operator << (ostream&, const Singly_Linked_List<E>&); // Overloaded output operator

    // Member functions
    size_t size() const; // Returns the size of the list
    bool empty() const; // Tests whether the list is empty
    T& front(); // Reads the first element of the list (l-value)
    const T& front() const; // Reads the first element of the list (r-value)
    T& back(); // Reads the last element of the list (l-value)
    const T& back() const; // Reads the last element of the list (r-value)
    void push_front(const T&); // Inserts an element at the front of the list
    void pop_front(); // Removes the first element of the list
    void push_back(const T&); // Inserts an element at the back of the list
    void pop_back(); // Removes the last element of the list
    void push_after(const T&, const T&); // Inserts an element after a specified element in the list
    void pop_after(const T&); // Removes the element after a specified element in the list
    void push_before(const T&, const T&); // Inserts an element before a specified element in the list
    void pop_before(const T&); // Removes the element before a specified element in the list
    void clear(); // Removes all elements from the list

    bool is_circular() const; // Tests whether the list is circular

private:
    /* A Singly Linked List Node */
    struct Node {
        // Data fields
        T data; // Stores the data of the node
        Node* next; // Pointer to the next node in the list

        // Constructor
        Node(const T&);
    };
    
    // Data fields 
    Node* head; // Stores the pointer to the first node.
    Node* tail; // Stores the pointer to the last node.
    size_t num_of_nodes; // Stores the number of nodes in the list.
};

/* Implementation of Singly_Linked_List */

// Constructor for Node
template <class T>
Singly_Linked_List<T>::Node::Node(const T& data) : data(data), next(nullptr) {}

// Constructor for Singly_Linked_List

// Default constructor
template <class T>
Singly_Linked_List<T>::Singly_Linked_List() : head(nullptr), tail(nullptr), num_of_nodes(0) {} 

// Copy constructor
template <class T>
Singly_Linked_List<T>::Singly_Linked_List(const Singly_Linked_List<T>& other) {
    // Step 1: set all pointers to nullptr
    head = nullptr;
    tail = nullptr;
    num_of_nodes = 0;
    // Step 2: set *this to other
    *this = other;
}

// Destructor: release the dynamically allocated memory
template <class T>
Singly_Linked_List<T>::~Singly_Linked_List() {
    clear(); // Clear the list to free memory
}

// Deep-copy assignment operator
template <class T>
const Singly_Linked_List<T>& Singly_Linked_List<T>::operator = (const Singly_Linked_List<T>& rhs) {
    // Step 1: avoid self-assignment
    if (this != &rhs) {
        // Step 2: delete all the current dynamically allocated memory
        clear();
        // Step 3: copy static data fields
        num_of_nodes = rhs.num_of_nodes;
        if(num_of_nodes) {
            // Step 4: copy dynamic data fields
            head = tail = new Node(rhs.head->data); // Create the first node
            const Node* current_rhs = rhs.head->next; // Pointer to traverse the rhs list
            while (current_rhs) {
                tail->next = new Node(current_rhs->data);
                tail = tail->next;
                current_rhs = current_rhs->next;
            }
        }
    }
    // Step 5: return
    return *this;
} // Time complexity: O(n)

// Gets the size of the list
template <class T>
size_t Singly_Linked_List<T>::size() const {
    return num_of_nodes;
} // Time complexity: O(1)

// Tests whether the list is empty
template <class T>
bool Singly_Linked_List<T>::empty() const {
    return !size();
} // Time complexity: O(1)

/** Reads the first element in the list (l-value) */
template <class T>
T& Singly_Linked_List<T>::front() {
    if (empty()) {
        throw std::out_of_range("List is empty");
    }
    return head->data;
} // Time complexity: O(1)

/** Reads the first element in the list (r-value) */
template <class T>
const T& Singly_Linked_List<T>::front() const {
    if (empty()) {
        throw std::out_of_range("List is empty");
    }
    return head->data;
} // Time complexity: O(1)

/*  Reads the last element in the list (l-value) */
template <class T>
T& Singly_Linked_List<T>::back() {
    if (empty()) {
        throw std::out_of_range("List is empty");
    }
    return tail->data;
} // Time complexity: O(1)

/** Reads the last element in the list (r-value) */
template <class T>
const T& Singly_Linked_List<T>::back() const {
    if (empty()) {
        throw std::out_of_range("List is empty");
    }
    return tail->data;
} // Time complexity: O(1)






/** Inserts a new element to the front of the list.
    @param value: the value of the new element to be added.
 */
template <class T>
void Singly_Linked_List<T>::push_front(const T& value) {
    Node* new_node = new Node(value);
    new_node->next = head; // Point the new node to the current head
    head = new_node; // Update the head to the new node

    // If the list was empty, set tail to head
    if (!tail) {
        tail = head; 
    }

    ++num_of_nodes; // Increment the number of nodes
} // Time complexity: O(1)

/** Removes the first element from the list.
    @return: the value of the removed element.
 */
template <class T>
void Singly_Linked_List<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("List is empty");
    }
    Node* temp = head; // Store the current head
    head = head->next; // Move head to the next node
    delete temp; // Delete the old head
    num_of_nodes--; // Decrement the number of nodes

    // If the list is now empty, set tail to nullptr
    if (!head) {
        tail = nullptr;
    }
} // Time complexity: O(1)


/** Insert a new node at the end of the linked list.
    @param head: a pointer to the first node in the linked list.
    @param value: the value of the new node to be inserted.
    @return: a pointer to the modified linked list.
*/
template <class T>
void Singly_Linked_List<T>::push_back(const T& value) {
    Node* new_node = new Node(value);
    if (!head) {
        head = tail = new_node; // If the list is empty, set both head and tail to the new node
    }
    tail->next = new_node; // Link the last node to the new node
    tail = new_node; // Update the tail to the new node
    ++num_of_nodes; // Increment the number of nodes
} // Time complexity: O(1)

/** Removes the last element from the list.
    @return: the value of the removed element.
 */
template <class T>
void Singly_Linked_List<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("List is empty");
    }
    if (head == tail) { // If there's only one node
        delete head; // Delete the only node
        head = nullptr; // Set head to nullptr
        tail = nullptr; // Set tail to nullptr
    } else {
        Node* current = head;
        while (current->next != tail) { // Traverse to the second last node
            current = current->next;
        }
        delete tail; // Delete the last node
        tail = current; // Update the tail to the second last node
        tail->next = nullptr; // Set the new tail's next to nullptr
    }
    num_of_nodes--; // Decrement the number of nodes
} // Time complexity: O(n)

/** Insert a new node after a specified node in the linked list.
    @param head: a pointer to the first node in the linked list.
    @param target: the value of the node after which to insert the new node.
    @param value: the value of the new node to be inserted.
    @return: a pointer to the modified linked list.
*/
template <class T>
void Singly_Linked_List<T>::push_after(const T& target, const T& value) {
    Node* current = head;
    while (current) {
        if (current->data == target) {
            Node* new_node = new Node(value);
            new_node->next = current->next; // Link the new node to the next node
            current->next = new_node; // Link the current node to the new node

            // Updates tail if inserting after the last node
            if (current == tail) {
                tail = new_node;
            }
            ++num_of_nodes; // Increment the number of nodes
            return; // Return the original head of the list
        }
        current = current->next; // Move to the next node
    }
} // Time complexity: O(n)

/** Removes the node after a specified node in the linked list.
    @param target: the value of the node after which to remove the next node.
*/
template <class T>
void Singly_Linked_List<T>::pop_after(const T& target) {
    Node* current = head;
    while (current && current->next) {
        if (current->data == target) {
            Node* temp = current->next; // Store the node to be deleted
            current->next = temp->next; // Link the current node to the node after the target

            if (temp == tail) { // If the target node is the tail, update the tail
                tail = current;
            }

            delete temp; // Delete the target node
            --num_of_nodes; // Decrement the number of nodes
            return; // Return after deletion
        }
        current = current->next; // Move to the next node
    }
} // Time complexity: O(n)


template <class T>
void Singly_Linked_List<T>::push_before(const T& target, const T& value) {
    if (!head) {
        return; // List is empty, nothing to insert before
    }

    // If the target is the head, insert at the front
    if (head->data == target) {
        push_front(value);
        return; // Return the new head
    }

    Node* current = head;
    while (current->next) {
        if (current->next->data == target) {
            Node* new_node = new Node(value);
            new_node->next = current->next; // Link the new node to the target node
            current->next = new_node; // Link the current node to the new node

            ++num_of_nodes; // Increment the number of nodes
            return; // Return the original head of the list
        }
        current = current->next; // Move to the next node
    }
} // Time complexity: O(n)

template <class T>
void Singly_Linked_List<T>::pop_before(const T& target) {
    if (!head || head->data == target) {
        return; // List is empty or target is the head, nothing to remove before
    }

    Node* previous = nullptr;
    Node* current = head;
    while (current->next) {
        if (current->next->data == target) {
            if (current == head) {
                pop_front(); // Remove the head if it's the node before the target
            } else {
                previous->next = current->next; // Link the previous node to the target node
                delete current; // Delete the node before the target
                --num_of_nodes; // Decrement the number of nodes
            }
            return; // Return after deletion
        }
        previous = current;
        current = current->next; // Move to the next node
    }
} // Time complexity: O(n)

template <class T>
void Singly_Linked_List<T>::clear() {
    while (head) {
        Node* current = head;
        head = head->next; // Move head to the next node
        delete current; // Delete the current node
    }
    tail = nullptr; // Set tail to nullptr
    num_of_nodes = 0; // Reset the number of nodes
 } // Time complexity: O(n)

// Stream insertin operator
template <class T>
ostream&  operator << (ostream& os, const Singly_Linked_List<T>& list) {
    const typename Singly_Linked_List<T>::Node* current = list.head;
    os << "[head -> ";
    while (current) {
        os << current->data;
        if (current->next) {
            os << " -> ";
        }
        current = current->next;
    }
    os << " <- tail]";
    return os;

} // Time complexity: O(n)

/*  Tests whether a singly linked list is circular.
    @param node: a pointer to a node in the linked list.
    @return: {true} if the list is circular, {false} otherwise.
*/
template <class T>
bool Singly_Linked_List<T>::is_circular() const {
    Node* slow = head;
    Node* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return true; // The list is circular
        }
    }
    return false; // The list is not circular
} // Time complexity: O(n)

#endif // SINGLY_LINKED_LIST_H