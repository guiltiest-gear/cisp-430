#include <iostream>

#include "ListNodecpp.h"

using std::cout;

// REMEMBER each ListNode has two parts : a data field
// and an address field. The address is either null or points to the next node
// in the chain
// Requires: integer value for searching, address of front
// Effects: traverses the list node chain starting from front until the end
// comparing search value with listnode getData. Returns the original  search
// value if found, if not adds +1 to indicate not found Modifies: Nothing
int search(ListNode<int> *front, int value);

// Requires: integer value for inserting, address of front
// Effects: creates a new ListNode with value and inserts in proper position
// (increasing order)in the chain. If chain is empty, adds to the beginning
// Modifies: front, if node is added at the beginning.
// Also changes the next pointer of the previous node to point to the
// newly inserted list node. the next pointer of the newly inserted pointer
// points to what was the next of the previous node.
// This way both previous and current links are adjusted
void insert(ListNode<int> *&front, int value);

// Requires: integer value for adding, address of front
// Effects:creates a new ListNode with value and inserts at the beginning
// Modifies:front, if node is added at the beginning.
void addNode(ListNode<int> *&front, int value);

// Requires: integer value for removing, address of front
// Effects: removes a node, if list is empty or node not found, removes nothing.
// Modifies: If the first node is removed, front is adjusted.
// if removal is at the end or middle, makes sure all nececssary links are
// updated.
void remove(ListNode<int> *&front, int value);

// Requires: address of front
// Effects: prints data of each node, by traversing the chain starting from the
// front using next pointers.
// Modifies: nothing
void printList(ListNode<int> *front);

// GIVEN
int main() {
  // Add 3 Nodes  to the chain of ListNodes
  // note AddNode method appends to the end so this will be out of order
  // the order of the nodes is 1, 2, 4
  // Create a daisy chain aka Linked List
  ListNode<int> *front = nullptr;
  printList(front);
  cout << "**********************\n";
  addNode(front, 1);
  printList(front);
  cout << "**********************\n";
  addNode(front, 2);
  printList(front);
  cout << "**********************\n";
  addNode(front, 4);
  printList(front);
  cout << "**********************\n";
  // the insert method inserts node with value 3 in place
  insert(front, 3);
  printList(front);
  cout << "**********************\n";
  // remove the first, so front needs to point to second
  remove(front, 1);
  printList(front);
  cout << "**********************\n";
  // insert it back
  insert(front, 1);
  printList(front);
  cout << "**********************\n";
  // remove from the middle
  remove(front, 3);
  printList(front);
  cout << "**********************\n";
  // remove at the end
  remove(front, 4);
  printList(front);
  cout << "**********************\n";
  // remove a non existent node
  remove(front, 5);
  printList(front);
  cout << "**********************\n";
  // remove all nodes one by one leaving only front pointing to null pointer
  remove(front, 2);
  printList(front);
  cout << "**********************\n";
  remove(front, 1);
  printList(front);
  cout << "**********************\n";
  // insert at the beginning of the empty list a larger value
  insert(front, 4);
  printList(front);
  cout << "**********************\n";
  // insert the smaller value at correct position in the front of the chain and
  // change front
  insert(front, 1);
  printList(front);
  cout << "**********************\n";
  return 0;
}

// GIVEN
void printList(ListNode<int> *front) {
  ListNode<int> *current = front;
  if (front == nullptr) {
    cout << "EMPTY LIST \n";
    return;
  }
  while (current != nullptr) {
    cout << current->getData() << '\n';
    current = current->getNext();
  }
}

// GIVEN
// searches the nodes starting from front, all the way to the end
// trying to match the given value with the data in the node.
// if found, it returns the value indicting found
// other wise it returns value +1 as a signal that item is not found
int search(ListNode<int> *front, int value) {
  ListNode<int> *current = front;
  while (current != nullptr && current->getData() != value)
    current = current->getNext();

  if (current != nullptr) return current->getData();
  return value + 1;
  // to indicate not found.
  // The calling program checks if return value is the same as search value
  // to know if its found; I was using *-1 but if search value is 0, then that
  // does not work;
}

// GIVEN
// creates a new node with data == value
void addNode(ListNode<int> *&front, int value) {
  ListNode<int> *current = front;
  ListNode<int> *temp = new ListNode<int>(value);
  if (front == nullptr) {
    front = temp;
    return;
  }

  while (current->getNext() != nullptr) current = current->getNext();

  current->setNext(temp);
}
// GIVEN
// remove the node that has the given integer value in its data field
void remove(ListNode<int> *&front, int value) {
  // we NEVER change front, unless the first item is deleted or
  // an item is added to the front of the list
  ListNode<int> *current = front;     // save the front in current
  ListNode<int> *previous = current;  // save the front as previous
  // initially both current and previous will point to front
  // then previous will lag behind current

  // keep moving along the list by following the next pointer
  // until either the item is found or we reach the end of the list
  while (current != nullptr && current->getData() != value) {
    previous = current;
    current = current->getNext();
  }

  // if the item is found in the middle or end of the list
  // then remove the item by skipping over it
  // is setting the next of the previous to the next of the current
  if (current != nullptr && current->getData() == value) {
    previous->setNext(current->getNext());

    // if found at the beginning, front needs to be changed to next of current
    if (current->getData() == front->getData()) {
      front = current->getNext();
      delete current;     // release and deallocate the deleted note
      current = nullptr;  // set the pointer to null so its not pointing to junk
    }
  }
}
// TODO - USE THE REMOVE ALGORITHM to help you to set current and previous links
// according

// TODO
void insert(ListNode<int> *&front, int value) {
  ListNode<int> *current = front;
  ListNode<int> *temp = new ListNode<int>(value);
  // Check if the list is empty, if so, just call addNode
  // Not sure why someone would call insert like this, but better to cover edge
  // cases too
  if (current == nullptr) {
    delete temp;
    temp = nullptr;
    addNode(front, value);
    return;
  }

  // Case where we're prepending to the list
  if (temp->getData() < current->getData()) {
    temp->setNext(current);
    front = temp;
    return;
  }

  // We need to figure out which next pointer contains data larger than value
  while (current->getNext() != nullptr &&
         current->getNext()->getData() < temp->getData())
    current = current->getNext();

  temp->setNext(current->getNext());
  current->setNext(temp);
}
