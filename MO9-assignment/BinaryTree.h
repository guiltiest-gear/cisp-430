#include "TreeNode.h"
class BinaryTree {
 private:
  TreeNode *root;
  int count;

 public:
  BinaryTree();
  void insert(int data);
  int getCount();
  void insert(int data, TreeNode *cur);
  void deleteNode(int data);
  // recursive search data methods
  int search(int data, int &noOfSteps);
  int search(int data, TreeNode *cur, int &noOfSteps);
  // recursive search Parent node methods
  TreeNode *searchPrev(int data);
  TreeNode *searchPrev(int data, TreeNode *prev);
  // recursive search methods
  TreeNode *searchNode(int data);
  TreeNode *searchNode(int data, TreeNode *cur);
  TreeNode *inorderSuccessor(TreeNode *cur);
  void inorderTraversal();
  void inorderTraversal(TreeNode *cur);
  void remove(TreeNode *t);
  bool hasOneChild(TreeNode *t);
  TreeNode *findNext(TreeNode *t);
};
