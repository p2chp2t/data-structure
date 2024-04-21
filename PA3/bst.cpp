#include "bst.h"
#include "tree.h"
#include <iostream>
#include <string>

using namespace std;

int BinarySearchTree::insert(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  if (existKey(_root, key))
    return -1;
  else
    _root = insertKey(_root, key);
  return 0;

  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int BinarySearchTree::remove(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  if (!existKey(_root, key) || _root == NULL)
    return -1;
  else
    _root = removeKey(_root, NULL, key);
  return 0;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

Node *BinarySearchTree::smallestKey(Node *node) {
  if (node == NULL)
    return NULL;
  if (node->left == NULL)
    return node;
  return smallestKey(node->left);
}

bool BinarySearchTree::existKey(Node *node, int key) {
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

Node *BinarySearchTree::insertKey(Node *node, int key) {
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

Node *BinarySearchTree::removeKey(Node *node, Node *parent, int key) {
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
