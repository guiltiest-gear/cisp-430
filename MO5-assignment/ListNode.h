#include <string>

template <class T>
class ListNode {
 private:
  T data;
  ListNode* next;

  // post: constructs a node with data 0 and null link
 public:
  ListNode();
  ListNode(T data);
  ListNode(T idata, ListNode<T>* newNext);
  std::string toString();
  ListNode<T>* getNext();
  void setNext(ListNode<T>* newNext);
  T getData();
  void setData(T newData);
};
