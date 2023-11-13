#ifndef LIST_HPP
#define LIST_HPP
/* List.hpp
 *
 * doubly-linked, double-ended list with Iterator interface
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

  //EFFECTS:  returns true if the list is empty
  bool empty() const {
    return first == nullptr;
  }

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow.  Instead, keep track of the size
  //         with a private member variable.  That's how std::list does it.
  int size() const {
    return list_size;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front() {
    assert(!empty());
    return first->datum;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back() {
    assert(!empty());
    return last->datum;
  }

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum) {
    Node *new_node = new Node{nullptr, first, datum};
    if (empty()) {
      last = new_node;
    } else {
        first->prev = new_node;
    }
    first = new_node;
    list_size++;
  }

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum) {
    Node *new_node = new Node{nullptr, last, datum};
    if (empty()) {
      first = new_node;
    } else {
        last->next = new_node;
    }
    last = new_node;
    list_size++;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front() {
    assert(!empty());
    Node *temp = first;
    first = first->next;
    if (first) {
      first->prev = nullptr;
    } else {
        last = nullptr;
    }
    delete temp;
    if (!empty()) {
      list_size--;
    }
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back() {
    assert(!empty());
    Node *temp = last;
    last = last->prev;
    if (last) {
      last->next = nullptr;
    } else{
        first = nullptr;
    }
    delete temp;
    if (!empty()) {
      list_size--;
    }
  }

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear() {
    while(!empty()) {
      pop_front();
    }
  }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists

  //default constructor
  List() : first(nullptr), last(nullptr), list_size(0) {}

  //destructor
  ~List() {
    clear();
  }

  //copy constructor
  List(const List<T> &other) : first(nullptr), last(nullptr), list_size(0) {
    copy_all(other);
  }

  //overloaded assignment operator
  List<T>& operator=(const List<T> &other) {
    if (this != &other) {
        clear();
        copy_all(other);
    }
    return *this;
  }

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other) {
    Node *current = other.first;
    while (current != nullptr) {
        push_back(current->datum); // push_back updates list_size
        current = current->next;
    }
  }

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty
  int list_size; // added variable to keep track of list size

public:
  ////////////////////////////////////////
  class Iterator {
    //OVERVIEW: Iterator interface to List

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.
  friend class List<T>;
  public:
    // Default constructor
    Iterator() : node_ptr(nullptr) {}

    // Dereference operator
    T& operator*() const {
      assert(node_ptr != nullptr); // or handle it more gracefully
      return node_ptr->datum;
    }

    // Pre-increment operator
    Iterator& operator++() {
      assert(node_ptr != nullptr); // or handle it more gracefully
      node_ptr = node_ptr->next;
      return *this;
    }

    // Equality comparison
    bool operator==(const Iterator &other) const {
      return node_ptr == other.node_ptr;
    }

    // Inequality comparison
    bool operator!=(const Iterator &other) const {
      return node_ptr != other.node_ptr;
    }

    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    Iterator& operator--() {
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }

  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here

    // add any friend declarations here

    // construct an Iterator at a specific position
    Iterator(Node *p) : node_ptr(p) {}

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const {
    return Iterator(nullptr);
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i) {
    assert(i.node_ptr != nullptr); // Ensure the iterator is valid

  Node *target = i.node_ptr;
  if (target->prev) {
    target->prev->next = target->next;
  } else {
    first = target->next; // If erasing the first element
  }

  if (target->next) {
    target->next->prev = target->prev;
  } else {
    last = target->prev; // If erasing the last element
  }

  delete target;
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum) {
    Node *new_node = new Node{nullptr, nullptr, datum};

    // If inserting at the beginning of the list or into an empty list
    if (i.node_ptr == first || i.node_ptr == nullptr) {
        new_node->next = first;
        if (first != nullptr) {
            // List is not empty
            first->prev = new_node;
        } else {
            // Inserting into an empty list
            last = new_node;
        }
        first = new_node;
    } else {
        // Inserting in the middle or end of the list
        new_node->next = i.node_ptr;
        new_node->prev = i.node_ptr->prev;
        i.node_ptr->prev->next = new_node;
        i.node_ptr->prev = new_node;
    }
  }

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


#endif // Do not remove this. Write all your code above this line.
