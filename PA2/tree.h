#pragma once
#include <string>

using namespace std;

struct Node {
  Node(char input_value) : value(input_value), left(NULL), right(NULL) {}
  char value;
  Node *left;
  Node *right;
};

class BinaryTree {
public:
  BinaryTree() { _root = NULL; };
  ~BinaryTree() {
    delete[] _root;
    _root = NULL;
  };
  void buildFromString(const char *data);

  string preOrder(int node_value);
  string postOrder(int node_value);
  string inOrder(int node_value);
  int getDepth(int node_value);
  bool isReverseComplete();

private:
  Node *_root;
  Node *_buildFromString(const char *data, int start, int end);
  /////////////////////////////////////////////////////////
  //////  TODO: Add Private members if required ///////////
  Node *target = NULL;
  int depth = 0;
  void findNode(Node *node, int value);
  void in_preOrder(string *answer, Node *node);
  void in_postOrder(string *answer, Node *node);
  void in_inOrder(string *answer, Node *node);
  void cal_depth(Node *root, int, int tmp = 0);
  bool isReverseCompleteHelper(Node *node);
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
};
