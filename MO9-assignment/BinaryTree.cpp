#include <iostream>
// inserts into sorted position as per inorder traversal
#include "BinaryTree.h"

using std::cout;

// default constructor
BinaryTree::BinaryTree() {
  root = nullptr;
  count = 0;
}

// insert node in sorted order in the tree
void BinaryTree::insert(int data, TreeNode *cur) {
  if (cur->getData() == data) return;
  if (data < cur->getData()) {
    if ((cur->getLeft()) == nullptr)
      cur->setLeft(new TreeNode(data, nullptr, nullptr));
    else
      insert(data, cur->getLeft());
  } else {
    if ((cur->getRight()) == nullptr)
      cur->setRight(new TreeNode(data, nullptr, nullptr));
    else
      insert(data, cur->getRight());
  }
}

// does not insert duplicates
void BinaryTree::insert(int data) {
  if (root == nullptr)
    root = new TreeNode(data, nullptr, nullptr);
  else
    insert(data, root);
  count++;
}

// releases a node to the heap
void BinaryTree::remove(TreeNode *t) { delete t; }
// checks if the node has only one child
// this method is used by delete function
bool BinaryTree::hasOneChild(TreeNode *t) {
  return (t->getLeft() == nullptr) ^ (t->getRight() == nullptr);
}

// get the left or right successor
TreeNode *BinaryTree::findNext(TreeNode *t) {
  if (t->getLeft() != nullptr)
    return t->getLeft();
  else
    return t->getRight();
}

// delete node
void BinaryTree::deleteNode(int data) {
  TreeNode *prev = root;
  TreeNode *found;
  // if tree is empty exit - no deletion needs to be done
  if (root == nullptr) exit(1);

  // search for the node that is to be deleted
  // if not found  exit
  found = searchNode(data, prev);
  if (found == nullptr) {
    cout << "\nNODE NOT FOUND " << data << '\n';
    exit(1);
  }
  // if found, search for its parent (prev) using the searchPrev(data)
  // method
  // there are three cases to be taken care of

  count--;
  prev = searchPrev(data);
  TreeNode *next;
  // Case 1. if the node to be deleted is a leaf (use isLeaf Method)
  // determine if its the left or right child of parent and set
  // that link to null pointer and release memory of (using remove method)
  // the found node
  if (found->isLeaf()) {
    // prev contains the parent node
    // Figure out if found is the left or right now
    // Try the right node first
    // nullptr comparison shouldn't be necessary, as found is guaranteed to
    // contain a valid node
    if (prev->getRight()->getData() == found->getData()) {
      // Delete found and set the right pointer to nullptr
      remove(found);
      prev->setRight(nullptr);
      // Exit the function
      return;
    }
    // If that doesn't pass, then the only other way for this to be valid is for
    // the left node
    remove(found);
    prev->setLeft(nullptr);
  } else if (hasOneChild(found)) {
    // 2. has either One child right or left branch
    // find the successor using the findNext method
    // set the parents right or left node to successor
    // this will depend on whether the found node is the right or left child
    // of parent
    // release found node

    // Figure out which node is next
    next = findNext(found);
    // Next now contains the child of found
    // Figure out if found is the right or left child
    // Try the right first
    if (prev->getRight() == found)
      prev->setRight(next);
    else if (prev->getLeft() == found)
      prev->setLeft(next);
    // Delete the found node
    remove(found);
  } else {
    // two child nodes
    // Case 3. The found node has a right and left child (or possibly right
    // and left subtree) This case is a little more complex.
    // In this case, the inOrder successor of the found node needs to be
    // searched and attached to the parent. find in order successor
    // determine if the found node is the left or right child of the parent
    // and set the next of the parent to the inorder successor
    // if the node to be deleted is the root then the root also has be
    // set accordindly
    TreeNode *successor = inorderSuccessor(found);
    // Check if the found node is the root
    if (found != root)
      found->setLeft(successor->getRight());
    else
      found->setRight(successor->getRight());
    // Copy the successor's data
    root->setData(successor->getData());
    // Delete the successor
    remove(successor);
  }
}

// return the number of nodes in the tree
int BinaryTree::getCount() { return count; }
// search for a node. If found it returns 0 otherwise -1
// also counts the number of steps taken for the search
int BinaryTree::search(int data, int &noOfSteps) {
  int depth = 0;
  if (root == nullptr) return -1;
  return search(data, root, noOfSteps);
}

int BinaryTree::search(int data, TreeNode *cur, int &noOfSteps) {
  if (cur == nullptr) {
    return -1;
  } else {
    if (cur->getData() == data)
      return 0;
    else if (data < cur->getData()) {
      noOfSteps++;
      return search(data, cur->getLeft(), noOfSteps);
    } else {
      noOfSteps = noOfSteps + 1;
      return search(data, cur->getRight(), noOfSteps);
    }
  }
}
// search function that returns the pointer to the node containing the data if
// found. Otherwise returns nullptr
TreeNode *BinaryTree::searchNode(int data) {
  if (root == nullptr) return nullptr;
  return searchNode(data, root);
}

TreeNode *BinaryTree::searchNode(int data, TreeNode *cur) {
  if (cur == nullptr) {
    return nullptr;
  } else {
    if (cur->getData() == data)
      return cur;
    else if (data < cur->getData())
      return searchNode(data, cur->getLeft());
    else
      return searchNode(data, cur->getRight());
  }
}

// find the parent node
TreeNode *BinaryTree::searchPrev(int data) {
  int depth = 0;

  if (root == nullptr) return nullptr;
  if (root->getData() == data) return root;
  return searchPrev(data, root);
}

TreeNode *BinaryTree::searchPrev(int data, TreeNode *prev) {
  if (prev->getLeft() == nullptr && prev->getRight() == nullptr) return prev;

  if (prev->getLeft() != nullptr && (prev->getLeft())->getData() == data)
    return prev;
  else if (prev->getRight() != nullptr && (prev->getRight())->getData() == data)
    return prev;
  if (data < prev->getData())
    return searchPrev(data, prev->getLeft());
  else
    return searchPrev(data, prev->getRight());
}

// find the in order successor
TreeNode *BinaryTree::inorderSuccessor(TreeNode *cur) {
  if (cur == nullptr)
    return nullptr;
  else if (cur->getRight() != nullptr)
    cur = cur->getRight();
  while (cur->getLeft() != nullptr) cur = cur->getLeft();
  return cur;
}

// in order traversal - achieved by processing the left most node
// then the parent of this leftmose node. This is followed by the in order
// traversal of the right child of the parent.
void BinaryTree::inorderTraversal(TreeNode *cur) {
  if (cur == nullptr) return;
  if (cur->getLeft() != nullptr) {
    inorderTraversal(cur->getLeft());
    cout << cur->getData() << " ";
  } else {
    cout << cur->getData() << " ";
  }
  if (cur->getRight() != nullptr) inorderTraversal(cur->getRight());
}

void BinaryTree::inorderTraversal() {
  if (root == nullptr)
    cout << "TREE IS EMPTY \n";
  else
    inorderTraversal(root);
  cout << "\n";
}
