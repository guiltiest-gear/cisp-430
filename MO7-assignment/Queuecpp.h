#include <string>

#include "Queue.h"

template <class T>
Queue<T>::Queue() {
  back = nullptr;
}

// add an element t to the end queue
// this should be an O(1) operation
template <class T>
void Queue<T>::add(T t) {
  // Create a new element
  ListNode<T>* tmp = new ListNode<T>(t, nullptr);
  if (Queue<T>::front == nullptr) {
    // This should happen if the queue is empty
    Queue<T>::front = tmp;
    Queue<T>::back = tmp;
  } else {
    // And when the queue is not
    Queue<T>::back->next = tmp;
    Queue<T>::back = tmp;
  }
}

// remove an element from the front of the queue
// this should be an O(1) operation
template <class T>
void Queue<T>::remove() {
  // Check if the queue is empty first
  if (Queue<T>::front == nullptr)
    // If it is, throw an exception
    throw std::string("NULL POINTER EXCEPTION QUEUE IS EMPTY");
  // Reuse the remove method to remove the data at the front
  // LinkedList<T>::remove(Queue<T>::front);
  Queue<T>::front = Queue<T>::front->next;
}
