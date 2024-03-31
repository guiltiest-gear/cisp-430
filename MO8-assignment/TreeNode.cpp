#include "TreeNode.h"

// Default constructor
TreeNode::TreeNode() {
  data = 0;
  left = nullptr;
  right = nullptr;
}

// Data-only constructor
TreeNode::TreeNode(int data) {
  this->data = data;
  this->left = nullptr;
  this->right = nullptr;
}

// Regular constructor
TreeNode::TreeNode(int data, TreeNode *left, TreeNode *right) {
  this->data = data;
  this->left = left;
  this->right = right;
}

// Sets the data for the current tree node
void TreeNode::setData(int data) { this->data = data; }
// Gets the data for the current tree node
int TreeNode::getData() { return data; }

// Gets the left tree node
TreeNode *TreeNode::getLeft() { return left; }
// Gets the right tree node
TreeNode *TreeNode::getRight() { return right; }

// does not create any new node. Just sets the right pointer
void TreeNode::setRight(TreeNode *newRight) { right = newRight; }
// does not create any new node. Just sets the left pointer
void TreeNode::setLeft(TreeNode *newLeft) { left = newLeft; }

// Determines if the current node is a leaf node
bool TreeNode::isLeaf() { return (left == nullptr && right == nullptr); }
// creates a new node with the data value and sets the right pointer to it
void TreeNode::addRight(int data) { right = new TreeNode(data); }
// creates a new node with the data value and sets the left pointer to it
void TreeNode::addLeft(int data) { left = new TreeNode(data); }
