#include "TreeNode.h"

TreeNode::TreeNode() {
  data = -1;
  left = nullptr;
  right = nullptr;
}

TreeNode::TreeNode(int data, TreeNode *left, TreeNode *right) {
  this->data = data;
  this->left = left;
  this->right = right;
  // std::cout<<"IN CONSTRUCTOR "<<this->data<<std::endl;
}

void TreeNode::setData(int data) { this->data = data; }
int TreeNode::getData() { return data; }
TreeNode *TreeNode::getLeft() { return left; }
TreeNode *TreeNode::getRight() { return right; }
void TreeNode::setRight(TreeNode *newRight) { right = newRight; }
void TreeNode::setLeft(TreeNode *newLeft) { left = newLeft; }
bool TreeNode::isLeaf() { return (left == nullptr && right == nullptr); }
