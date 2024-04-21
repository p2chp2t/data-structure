#include "dabst.h"
#include "bst.h"
#include "tree.h"
#include <iostream>
#include <string>

using namespace std;

string DABSTree::inOrder() {
  string output;
  _inOrder(output, _root);
  if (!output.empty())
    output.pop_back();
  return output;
}

string DABSTree::preOrder() {
  string output;
  _preOrder(output, _root);
  if (!output.empty())
    output.pop_back();
  return output;
}

void DABSTree::_inOrder(string &output, Node *cur) {
  if (cur == NULL)
    return;
  _inOrder(output, cur->left);
  output.append(cur->print_key());
  output.append("(");
  output.append(cur->print_count());
  output.append(")");
  output.append(" ");
  _inOrder(output, cur->right);
}

void DABSTree::_preOrder(string &output, Node *cur) {
  if (cur == NULL)
    return;
  output.append(cur->print_key());
  output.append("(");
  output.append(cur->print_count());
  output.append(")");
  output.append(" ");
  _preOrder(output, cur->left);
  _preOrder(output, cur->right);
}

int DABSTree::insert(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  Node *target = searchKey(_root, key);
  if (target == NULL) {
    _root = insertKey(_root, key);
  } else { // same key already exists
    target->count++;
  }
  return 0;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int DABSTree::remove(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  Node *target = searchKey(_root, key);
  if (target == NULL) { // key doesn't exist
    return -1;
  }
  if (target != NULL) { // same key exists
    target->count--;
    if (target->count == 0) {
      _root = removeKey(_root, NULL, key);
      return 1;
    }
  }
  return 0;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */
Node *DABSTree::smallestKey(Node *node) {
  if (node == NULL)
    return NULL;
  if (node->left == NULL)
    return node;
  return smallestKey(node->left);
}

Node *DABSTree::searchKey(Node *node, int key) {
  while (node != NULL) {
    if (key == node->key) {
      return node;
    } else if (key < node->key) {
      node = node->left;
    } else if (key > node->key) {
      node = node->right;
    }
  }
  return NULL;
}

Node *DABSTree::insertKey(Node *node, int key) {
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

Node *DABSTree::removeKey(Node *node, Node *parent, int key) {
  if(node==NULL)
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