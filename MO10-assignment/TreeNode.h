class TreeNode {
 private:
  int data;
  TreeNode *left;
  TreeNode *right;

 public:
  TreeNode();
  TreeNode(int data, TreeNode *left, TreeNode *right);
  void setData(int data);
  int getData();
  bool isLeaf();
  TreeNode *getLeft();
  TreeNode *getRight();
  void setRight(TreeNode *newRight);
  void setLeft(TreeNode *newLeft);
};
