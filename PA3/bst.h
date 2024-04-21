#pragma once
#include "tree.h"

using namespace std;

class BinarySearchTree : public BinaryTree {
public:
  BinarySearchTree(){};
  ~BinarySearchTree(){};

  int insert(int key);
  int remove(int key);

private:
  /////////////////////////////////////////////////////////
  //////  TODO: Add private members if required ///////////
  Node *smallestKey(Node *node);
  bool existKey(Node *node, int key);
  Node *insertKey(Node *node, int key);
  Node *removeKey(Node *node, Node *parent, int key);
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
};