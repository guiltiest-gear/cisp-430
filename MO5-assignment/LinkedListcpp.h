#include <iostream>
#include <string>

#include "LinkedList.h"

// GIVEN
template <class T>
LinkedList<T>::LinkedList() {
  front = nullptr;
  count = 0;
}

// GIVEN
template <class T>
bool LinkedList<T>::empty() {
  return (front == nullptr);
}

// GIVEN
template <class T>
int LinkedList<T>::size() {
  return count;
}

// GIVEN
// add is more efficient since it adds at the front
// this is different from add of the Assignment 4 which adds at the end of List,
// so really the question is if we are going to add in order, then why make it
// more inefficient
template <class T>
void LinkedList<T>::add(T t) {
  ListNode<T>* e = new ListNode<T>(t, front);
  front = e;
  count++;
}

/*
template <class T>
std::string LinkedList<T>:: toString(int i){
   return get(i).toString();
}
*/

// GIVEN
template <class T>
void LinkedList<T>::printList() {
  ListNode<T>* current = front;
  while (current != nullptr) {
    std::cout << current->toString() << '\n';
    current = current->getNext();
  }
}

// Requires: Song for inserting
// Effects: creates a new ListNode with input value and inserts in proper
// position (increasing order of chart position)in the chain. If LinkedList,
// adds to the beginning
// Modifies: front, if node is added at the beginning.
// Also changes the next pointer of the previous node to point to the newly
// inserted list node. the next pointer of the newly inserted pointer points to
// what was the next of the previous node. This way both previous and current
// links are adjusted
// TODO
template <class T>
int LinkedList<T>::insert(T value, SortBy<T> f) {
  int steps = 0;
  // Create a new node to insert
  ListNode<T>* new_node;
  // Create a reference to front
  ListNode<T>* current = front;
  // If front is a nullptr, it must be empty, insert as usual
  if (front == nullptr) {
    steps++;
    new_node = new ListNode<T>(value);
    front = new_node;
    return steps;
  }

  if (f(value, current->getData())) {
    steps++;
    new_node = new ListNode<T>(value);
    new_node->setNext(front);
    front = new_node;
    return steps;
  }

  while (current != nullptr && current->getData() <= value) {
    current = current->getNext();
    steps++;
  }

  if (current != nullptr) {
    new_node = new ListNode<T>(value, current->getNext());
    current->setNext(new_node);
    steps++;
  }

  return steps;
}

// Requires: Song title for searching
// Effects: traverses the LinkedList (database) starting from front until the
// end comparing titles Returns the original search value if found otherwise
// returns an empty song with blank title
// Modifies: Nothing
template <class T>
T LinkedList<T>::get(T value) {
  ListNode<T>* current = front;  // this may need to change
  // Loop until we hit a nullptr, which means we're at the end
  while (current != nullptr) {
    // Is this the node with the data we're looking for?
    if (current->getData() == value)
      // If so, return the original search value
      return value;

    // Go to the next node
    current = current->getNext();
  }
  // Create a default object to return
  T empty_object;
  return empty_object;
}

template <class T>
int LinkedList<T>::remove(T value) {
  int steps = 0;
  ListNode<T>* current = front;
  // Check if the front if the value we're attempting to remove
  if (current->getData() == value) {
    steps++;
    // Essentially perform the exact same steps as a normal removal
    ListNode<T>* remove_node = current;
    ListNode<T>* after = remove_node->getNext();
    delete remove_node;
    remove_node = nullptr;
    front = after;
    return steps;
  }
  // Loop through the list and figure out where the node is
  while (current->getNext() != nullptr && current != nullptr) {
    steps++;
    if (current->getNext()->getData() == value) {
      // Current is now right behind the pointer we want to remove
      // Save this pointer
      ListNode<T>* remove_node = current->getNext();
      // Now save the pointer just ahead of it
      ListNode<T>* after = remove_node->getNext();
      // Delete and nullify remove_node
      delete remove_node;
      remove_node = nullptr;
      // Now set current's next pointer to after
      current->setNext(after);
    } else {
      current = current->getNext();
    }
  }

  return steps;
}

// Requires: index position of Song to be found
// Effects: traverses the LinkedList starting from front and travels to the
// index position (if valid) and returns the song at that index position. Note
// index position may NOT be the same as chart position
// Modifies: Nothing
template <class T>
T LinkedList<T>::get(int index) {
  ListNode<T>* current = front;
  // Loop forward to the index
  // Assuming we're using zero-based indexing (like any sane person would), this
  // should work as intended
  for (int i = 0; i < index; i++) {
    current = current->getNext();
    // If we encounter a nullptr, abort, that's not a valid position
    if (current == nullptr) throw std::string("Not a valid index");
  }
  // If we got here, current must be a valid position
  // Proceed to return data at current
  return current->getData();
}
