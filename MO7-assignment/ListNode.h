#include <string>

template <class T>
class ListNode {
 public:
  T data;
  ListNode* next;
  ListNode();
  ListNode(T data);
  ListNode(T idata, ListNode<T>* inext);
  std::string toString();
  T getData();
};
