#include "avl.h"
#include "bst.h"
#include "tree.h"
#include <iostream>
#include <string>

using namespace std;

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */
int AVLTree::balFact(Node *node) {
  int left;
  int right;
  int diff;
  if (node == NULL)
    return 0;
  left = getHeight(node->left);
  right = getHeight(node->right);
  diff = left - right;
  return diff;
}

int AVLTree::getHeight(Node *node) {
  int lheight;
  int rheight;
  int height;
  if (node == NULL)
    return 0;
  lheight = getHeight(node->left);
  rheight = getHeight(node->right);
  height = (lheight > rheight) ? lheight + 1 : rheight + 1;
  return height;
}

Node *AVLTree::rotLL(Node *node) {
  Node *parent; // pivot node
  Node *child;
  parent = node;
  child = parent->left;
  parent->left = child->right;
  child->right = parent;
  return child;
}

Node *AVLTree::rotRR(Node *node) {
  Node *parent; // pivot node
  Node *child;
  parent = node;
  child = parent->right;
  parent->right = child->left;
  child->left = parent;
  return child;
}

Node *AVLTree::rotLR(Node *node) {
  Node *parent; // pivot node
  Node *child;
  parent = node;
  child = rotLL(rotRR(parent->left));
  return child;
}

Node *AVLTree::rotRL(Node *node) {
  Node *parent; // pivot node
  Node *child;
  parent = node;
  child = rotRR(rotLL(parent->right));
  return child;
}

Node *AVLTree::rebal(Node *node) {
  int bf = balFact(node);
  if (bf > 1) { // violation in left subtree
    if (balFact(node->left) > 0)
      node = rotLL(node);
    else
      node = rotLR(node);
  } else if (bf < -1) { // violation in right subtree
    if (balFact((node)->right) < 0)
      node = rotRR(node);
    else
      node = rotRL(node);
  }
  return node;
}

Node *AVLTree::smallestKey(Node *node) {
  if (node == NULL)
    return NULL;
  if (node->left == NULL)
    return node;
  return smallestKey(node->left);
}

bool AVLTree::existKey(Node *node, int key) {
  if (node == NULL)
    return false;
  while (node != NULL) {
    if (key == node->key)
      return true;
    else if (key < node->key)
      node = node->left;
    else
      node = node->right;
  }
  return false;
}

Node *AVLTree::insertKey(Node *node, int key) {
  if (node == NULL) {
    Node *newNode = new Node(key);
    return newNode;
  } else if (key < node->key) {
    node->left = insertKey(node->left, key);
  } else if (key > node->key) {
    node->right = insertKey(node->right, key);
  }
  return node;
}

Node *AVLTree::removeKey(Node *node, Node *parent, int key) {
  if (node == NULL)
    return node;
  if (key < node->key) {
    node->left = removeKey(node->left, node, key);
  } else if (key > node->key) {
    node->right = removeKey(node->right, node, key);
  } else {                                           // found key
    if (node->left == NULL && node->right == NULL) { // leaf node
      if (parent) {                                  // if parent node exists
        if (parent->left == node)
          parent->left = NULL;
        else if (parent->right == node)
          parent->right = NULL;
      }
      node = NULL;
    } else if (node->left == NULL || node->right == NULL) { // # of subtree is 1
      Node *temp = NULL; // subtree of node to remove
      if (node->left != NULL)
        temp = node->left;
      else
        temp = node->right;
      if (parent) { // if parent node exists
        if (parent->left == node)
          parent->left = temp;
        else if (parent->right == node)
          parent->right = temp;
      }
      node = temp;
    } else if (node->left != NULL && node->right != NULL) { // # of subtree is 2
      Node *smallest = smallestKey(node->right);
      node->key = smallest->key;
      node->right = removeKey(node->right, node, smallest->key);
    }
  }
  return node;
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

int AVLTree::insert(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  if (existKey(_root, key))
    return -1;
  else
    _root = insertKey(_root, key);
  _root = rebal(_root);
  return 0;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int AVLTree::remove(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  if (!existKey(_root, key) || _root == NULL)
    return -1;
  else
    _root = removeKey(_root, NULL, key);
  _root = rebal(_root);
  return 0;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}
