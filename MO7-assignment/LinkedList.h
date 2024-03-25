#include "ListNodecpp.h"

template <class T>
class LinkedList {
 protected:
  ListNode<T> *front;
  ListNode<T> *back;
  int count;

 public:
  LinkedList<T>();
  bool empty();
  int size();
  void add(T t);
  void remove(T t);
  void move(T t, int pos);
  void insert(T t, int pos);
  void insert(T t);
  int get(T t);
  std::string toString();
  void printList();
  void print(int number);
  bool operator==(T other);
  void printSong(int number);
  void adjustInsert(ListNode<T> *t, int increment);
  struct Iterator {
    ListNode<T> *cur;          //  a pointer to the current ListNode
    Iterator();                // constructs the Iterator object
    Iterator(ListNode<T> *t);  // custom constructor
    ListNode<T> *next();       // gets a pointer to the next ListNode in the q
    ListNode<T> *getCur();     // returns cur
    bool operator==(Iterator iter);  // used to compare  the current object with
                                     // the iterator, used to detect the end
    void operator++();         // increment iterator to move to next ListNode
    ListNode<T> *operator*();  // dereference to get the value of the ListNode
                               // being pointed to by iterator object
  };

  Iterator begin();
  Iterator end();
};
