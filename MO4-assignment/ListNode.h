#include <string>

// We can create a linked list wich contains items of type T
// in our assignments T will be either integer or Song
template <class T>
class ListNode {
 private:
  // the data field in our case would contain either an integer a Song
  T data;
  // this is a pointer to the next integer or Song
  ListNode* next;

 public:
  // default constructor constructs a node with
  // data value as the default data value for T and null link
  ListNode();
  // custom constructor #1 constructs a node with data value == data
  // and next == null
  explicit ListNode(T data);
  // custom constructor #2
  // constructs a node with data value = idata  and next == newNext
  ListNode(T idata, ListNode<T>* newNext);
  // Return the node data as a string
  std::string toString();
  // get the address of the next integer or Song
  ListNode<T>* getNext();
  // change the next address to newNext
  void setNext(ListNode<T>* newNext);
  // return the integer or Song
  T getData();
  // change the Song to newData
  void setData(T newData);
};
