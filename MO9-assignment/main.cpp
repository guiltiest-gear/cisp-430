#include <iostream>

#include "BinaryTree.h"

using std::cout;

int main() {
  BinaryTree tree;
  // create a tree with 13 nodes
  // the root will be 5 and inserting in order will give it 5 levels
  tree.insert(5);
  tree.insert(10);
  tree.insert(3);
  tree.insert(7);
  tree.insert(1);
  tree.insert(9);
  tree.insert(6);
  tree.insert(2);
  tree.insert(8);
  tree.insert(4);
  tree.insert(14);
  tree.insert(11);
  tree.insert(15);
  // print the tree in sorted order
  cout << "In Order Traversal\n";
  tree.inorderTraversal();
  // delete 4 nodes so that there is one path of depth 5 and all others are of
  // depth 3
  cout << "deleting node 2\n";
  tree.deleteNode(2);
  cout << "deleting node 6\n";
  tree.deleteNode(6);
  cout << "deleting node 11\n";
  tree.deleteNode(11);
  cout << "deleting node 15\n";
  tree.deleteNode(15);
  // print the tree in sorted order
  cout << "\nThe Tree after Deletions is:\n";
  tree.inorderTraversal();
  return 0;
}
