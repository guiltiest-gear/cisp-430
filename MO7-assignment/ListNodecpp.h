#include <iostream>

#include "ListNode.h"
template <class T>
// post: constructs a node with data 0 and null link
ListNode<T>::ListNode() {
  std::cout << " IN constructor" << std::endl;
  T t;
  next = nullptr;
}

template <class T>
ListNode<T>::ListNode(T idata) {
  data = idata;
  next = nullptr;
}

template <class T>
ListNode<T>::ListNode(T idata, ListNode<T>* inext) {
  data = idata;
  next = inext;
}

template <class T>
std::string ListNode<T>::toString() {
  return data.toString();
}

template <class T>
T ListNode<T>::getData() {
  return data;
}
