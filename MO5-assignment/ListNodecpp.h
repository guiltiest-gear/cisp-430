#include "ListNode.h"

template <class T>
// post: constructs a node with data 0 and null link
// GIVEN
ListNode<T>::ListNode() {
  data = 0;
  next = nullptr;
}

// Only assign data to node
template <class T>
ListNode<T>::ListNode(T idata) {
  data = idata;
  next = nullptr;
}

// Assign data and next pointer
template <class T>
ListNode<T>::ListNode(T idata, ListNode<T>* inext) {
  data = idata;
  next = inext;
}

// Return node data as a string
template <class T>
std::string ListNode<T>::toString() {
  return data.toString();
}

// Get the next pointer
template <class T>
ListNode<T>* ListNode<T>::getNext() {
  return next;
}

// Get the node data
template <class T>
T ListNode<T>::getData() {
  return data;
}

// Set the node next pointer
template <class T>
void ListNode<T>::setNext(ListNode<T>* newNext) {
  next = newNext;
}

// Set the node data
template <class T>
void ListNode<T>::setData(T newData) {
  data = newData;
}
