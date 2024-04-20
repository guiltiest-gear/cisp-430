#include <vector>

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
  void set(TreeNode *t, TreeNode *next);
  int search(int data, int &noOfSteps);
  int search(int data, TreeNode *cur, int &noOfSteps);
  TreeNode *searchPrev(int data);
  TreeNode *searchPrev(int data, TreeNode *prev);
  TreeNode *searchNode(int data);
  TreeNode *searchNode(int data, TreeNode *cur);
  TreeNode *inorderSuccessor(TreeNode *cur);
  void inorderTraversal();
  void inorderTraversal(TreeNode *cur);
  void balance();
  int height();
  int height(TreeNode *cur);
  void remove(TreeNode *t);
  void deleteTree();
  bool hasOneChild(TreeNode *t);
  TreeNode *findNext(TreeNode *t);
  void addToVector(std::vector<int> &treeVector, TreeNode *cur);
  void rebuild(std::vector<int> &treeVector);
  void rebuild(std::vector<int> &treeVector, int first, int last);
};
