#include "ListNodecpp.h"
#include "SortBycpp.h"

template <class T>
class LinkedList {
 private:
  ListNode<T>* front;
  int count;

 public:
  LinkedList<T>();
  bool empty();
  int size();
  void add(T t);
  T get(T value);
  T get(int index);
  int insert(T t, SortBy<T> f);
  int remove(T t);
  std::string toString();
  void printList();
};
