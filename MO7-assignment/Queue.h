#include "LinkedListcpp.h"

template <class T>
class Queue : public LinkedList<T> {
 private:
  ListNode<T>* back;

 public:
  Queue<T>();
  void add(T t);
  void remove();
  void remove(std::string title);
};
