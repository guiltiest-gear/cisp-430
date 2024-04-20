// inserts into sorted position as per inorder traversal
#include "BinaryTree.h"

#include <iostream>

using std::cout, std::vector;

BinaryTree::BinaryTree() {
  root = nullptr;
  count = 0;
}

int BinaryTree::getCount() { return count; }
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

void BinaryTree::remove(TreeNode *t) { delete t; }

bool BinaryTree::hasOneChild(TreeNode *t) {
  return (t->getLeft() == nullptr) ^ (t->getRight() == nullptr);
}

TreeNode *BinaryTree::findNext(TreeNode *t) {
  if (t->getLeft() != nullptr)
    return t->getLeft();
  else
    return t->getRight();
}

// deleteTree
void BinaryTree::deleteTree() {
  // ideally each node needs to be de
  delete root;
  root = nullptr;
  count = 0;
}

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

// delete
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

// search parent
TreeNode *BinaryTree::searchPrev(int data) {
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

// find in in order successor
TreeNode *BinaryTree::inorderSuccessor(TreeNode *cur) {
  if (cur == nullptr)
    return nullptr;
  else if (cur->getRight() != nullptr)
    cur = cur->getRight();

  while (cur->getLeft() != nullptr) cur = cur->getLeft();
  return cur;
}

// travers inorder (sorted order)
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
    cout << "TREE IS EMPTY\n";
  else
    inorderTraversal(root);
  cout << '\n';
}

// traverse the tree in order and add each element to the treeVector
// this creates a vector of tree Nodes in sorted order
// TODO
void BinaryTree::addToVector(vector<int> &treeVector, TreeNode *cur) {
  if (cur == nullptr) return;
  // Call addVector on the left subtree
  // Push current data to vector
  if (cur->getLeft() != nullptr) {
    addToVector(treeVector, cur->getLeft());
  }
  // Push back to current data
  treeVector.push_back(cur->getData());
  if (cur->getRight() != nullptr) {
    addToVector(treeVector, cur->getRight());
  }
}

// TODO
// successively and recursively divide the node vector and create a new
// balanced tree by inserting the middle node to the new tree using the insert
// function
// this method is a lot like recursive binary search
// except that the found node is inserted into the tree
void BinaryTree::rebuild(vector<int> &treeVector, int first, int last) {
  // call recursively untile first >last
  if (first > last) {
    return;
  }
  // find middle and insert into tree
  int mid = (first + last) / 2;
  insert(treeVector[mid]);
  rebuild(treeVector, first, mid - 1);
  rebuild(treeVector, mid + 1, last);
}

void BinaryTree::rebuild(vector<int> &treeVector) {
  delete root;
  root = nullptr;
  count = 0;
  rebuild(treeVector, 0, treeVector.size() - 1);
  inorderTraversal();
}

// balance the tree by traversing in order and copying all the nodes into a
// treeVector
// then rebuilding the tree
// GIVEN
void BinaryTree::balance() {
  vector<int> treeVector;
  if (root != nullptr) {
    addToVector(treeVector, root);
  } else {
    cout << "Tree is empty\n";
    exit(1);
  }
  rebuild(treeVector);
};

// compare heigths of subtrees and return the greater
int max(int a, int b) {
  if (a >= b)
    return a;
  else
    return b;
}

// find the height of the tree
// GIVEN
int BinaryTree::height(TreeNode *cur) {
  if ((cur->getLeft() != nullptr) && (cur->getRight() != nullptr))
    return 1 + max(height(cur->getLeft()), height(cur->getRight()));
  else if (cur->getLeft() == nullptr && cur->getRight() != nullptr)
    return 1 + height(cur->getRight());
  else if (cur->getLeft() != nullptr && (cur->getRight() == nullptr))
    return 1 + height(cur->getLeft());
  else
    return 0;
}

// GIVEN
int BinaryTree::height() {
  if (root == nullptr)
    return 0;
  else
    return height(root);
}
