#include "LinkedList.h"

template <class T>
LinkedList<T>::LinkedList() {
  front = nullptr;
  back = nullptr;
  count = 0;
}

template <class T>
bool LinkedList<T>::empty() {
  return (front == nullptr);
}

template <class T>
int LinkedList<T>::size() {
  return count;
}

template <class T>
void LinkedList<T>::add(T t) {
  ListNode<T> *e = new ListNode<T>(t, front);
  front = e;
  count++;
}

template <class T>
void LinkedList<T>::printList() {
  ListNode<T> *cur = front;
  while (cur != nullptr) {
    std::cout << cur->toString() << '\n';
    cur = cur->next;
  }
}

template <class T>
void LinkedList<T>::print(int number) {
  ListNode<T> *cur = front;
  int index = 0;
  while (cur != nullptr && index < number && index < count) {
    std::cout << cur->toString() << '\n';
    cur = cur->next;
    index++;
  }
}

template <class T>
void LinkedList<T>::printSong(int number) {
  ListNode<T> *cur = front;
  int index = 1;
  while (cur != nullptr && index < number && index < count) {
    cur = cur->next;
    index++;
  }
  if (cur != nullptr && index == number) std::cout << cur->toString() << '\n';
}

template <class T>
LinkedList<T>::Iterator::Iterator() {
  cur = nullptr;
}

template <class T>
LinkedList<T>::Iterator::Iterator(ListNode<T> *t) {
  cur = t;
}

template <class T>
ListNode<T> *LinkedList<T>::Iterator::next() {
  return cur->next;
}

template <class T>
ListNode<T> *LinkedList<T>::Iterator::getCur() {
  return cur;
}

template <class T>
bool LinkedList<T>::Iterator::operator==(Iterator iter) {
  return cur == iter.getCur();
}

template <class T>
ListNode<T> *LinkedList<T>::Iterator::operator*() {
  return cur;
}

template <class T>
void LinkedList<T>::Iterator::operator++() {
  if (cur != nullptr) cur = cur->next;
}

template <class T>
typename LinkedList<T>::Iterator LinkedList<T>::begin() {
  return Iterator(front);
}

template <class T>
typename LinkedList<T>::Iterator LinkedList<T>::end() {
  return Iterator(back);
}

template <class T>
bool LinkedList<T>::operator==(T other) {
  return *this == other;
}

template <class T>
void LinkedList<T>::remove(T t) {
  if (front == nullptr) {
    throw std::string("EMPTY LIST REMOVAL EXCEPTION\n");
    exit(1);
  } else if (front->data == t) {
    ListNode<T> *temp = front;
    front = front->next;
    adjustInsert(front, -1);
  } else {
    ListNode<T> *cur = front;
    ListNode<T> *prev = front;
    while ((cur != nullptr) && (!(cur->data == t))) {
      prev = cur;
      cur = cur->next;
    }

    if (cur != nullptr) {
      prev->next = cur->next;
      adjustInsert(cur->next, -1);
    }
  }
}

template <class T>
int LinkedList<T>::get(T t) {
  ListNode<T> *cur = front;

  int index = 0;
  while ((cur != nullptr) && (!(cur->data == t))) {
    cur = cur->next;
    index++;
  }
  if (cur == nullptr)
    return -1;
  else
    return index;
}

// If the song is found, remove it and insert in the given position
// If not found just insert it in the given position
template <class T>
void LinkedList<T>::move(T t, int pos) {
  int index = get(t);
  // The song must not be in here if this is the case
  if (index == -1) {
    insert(t, pos);
    return;
  }
  // Otherwise, the song we're looking for should be at index
  // Delete it, and then insert it into the new position
  remove(t);
  insert(t, pos);
}

template <class T>
void LinkedList<T>::adjustInsert(ListNode<T> *t, int increment) {
  ListNode<T> *current = t;
  while (current != nullptr) {
    (current->data)
        .setChartPosition((current->data).getChartPosition() + increment);
    current = current->next;
  }
}

template <class T>
void LinkedList<T>::insert(T t) {
  if (front == nullptr) {
    ListNode<T> *temp = new ListNode<T>(t, front);
    front = temp;
    back = temp;
  } else if (t < front->data) {
    ListNode<T> *temp = new ListNode<T>(t, front);
    front = temp;
    // adjustInsert(temp->next,1);

  } else {
    ListNode<T> *cur = front;
    ListNode<T> *prev = front;

    while ((cur != nullptr) && (cur->data < t)) {
      prev = cur;
      cur = cur->next;
    }
    ListNode<T> *temp = new ListNode<T>(t, cur);
    if (cur == nullptr) back = temp;
    prev->next = temp;
  }
  count++;
}

template <class T>
void LinkedList<T>::insert(T t, int pos) {
  int index = 1;
  ListNode<T> *cur = front;
  if ((pos == 1) || (front == nullptr)) {
    ListNode<T> *temp = new ListNode<T>(t, front);
    front = temp;

    // append to end of linked list
  } else if (pos > count) {
    if (cur != nullptr) {  // list is not empty
      while (cur->next != nullptr) cur = cur->next;
      ListNode<T> *temp = new ListNode<T>(t);
      cur->next = temp;
    }

  } else {
    while (index < pos - 1) {
      cur = cur->next;
      index++;
    }

    ListNode<T> *temp = new ListNode<T>(t, cur->next);
    cur->next = temp;

    adjustInsert(temp->next, 1);
  }
  count++;
}
