class TreeNode {
 private:
  int data;
  TreeNode *left;
  TreeNode *right;

 public:
  // Construtors
  TreeNode();
  TreeNode(int data);
  TreeNode(int data, TreeNode *left, TreeNode *right);

  // Getters
  int getData();
  TreeNode *getLeft();
  TreeNode *getRight();
  bool isLeaf();

  // Setters
  void setData(int data);
  void setRight(TreeNode *newRight);
  void setLeft(TreeNode *newLeft);

  // Creators
  void addRight(int data);
  void addLeft(int data);
};
