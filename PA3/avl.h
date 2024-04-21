#pragma once
#include "bst.h"

using namespace std;

class AVLTree : public BinarySearchTree {
public:
  AVLTree(){};
  ~AVLTree(){};

  int insert(int key);
  int remove(int key);

private:
  /////////////////////////////////////////////////////////
  //////  TODO: Add private members if required ///////////
  int balFact(Node *node);
  int getHeight(Node *node);
  Node *rotLL(Node *node);
  Node *rotRR(Node *node);
  Node *rotLR(Node *node);
  Node *rotRL(Node *node);
  Node *rebal(Node *node);
  Node *smallestKey(Node *node);
  bool existKey(Node *node, int key);
  Node *insertKey(Node *node, int key);
  Node *removeKey(Node *node, Node *parent, int key);
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
};