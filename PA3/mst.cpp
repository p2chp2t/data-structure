#include "mst.h"
#include <iostream>
#include <string>

using namespace std;

string MultiWayTree::preOrder() {
  string output;
  _preOrder(output, _root);
  if (!output.empty())
    output.pop_back();
  return output;
}

void MultiWayTree::_preOrder(string &output, MultiNode *cur) {
  if (cur == NULL)
    return;

  output.append(cur->print_key());
  output.append(" ");
  _preOrder(output, cur->left);
  _preOrder(output, cur->middle);
  _preOrder(output, cur->right);
}

int MultiWaySearchTree::insert(int key) {
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

int MultiWaySearchTree::remove(int key) {
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
MultiNode *MultiWaySearchTree::smallestKey(MultiNode *node) {
  if (node == NULL)
    return NULL;
  if (node->left == NULL)
    return node;
  return smallestKey(node->left);
}

MultiNode *MultiWaySearchTree::largestKey(MultiNode *node) {
  if (node == NULL)
    return NULL;
  if (node->right == NULL) {
    return node;
  }
  return largestKey(node->right);
}

bool MultiWaySearchTree::existKey(MultiNode *node, int key) {
  if (node == NULL)
    return false;
  while (node != NULL) {
    if (key == node->key1 || key == node->key2)
      return true;
    else if (key < node->key1)
      node = node->left;
    else if (key > node->key2)
      node = node->right;
    else // btw key1 and key2
      node = node->middle;
  }
  return false;
}

MultiNode *MultiWaySearchTree::insertKey(MultiNode *node, int key) {
  if (node == NULL) {
    MultiNode *newNode = new MultiNode();
    newNode->key1 = key;
    return newNode;
  }
  if (!node->isleaf()) {
    if (key < node->key1)
      node->left = insertKey(node->left, key);
    else if (key > node->key2)
      node->right = insertKey(node->right, key);
    else
      node->middle = insertKey(node->middle, key);
    return node;
  } else { // if it is leaf node, insert
    if (node->keyCount() == 1) {
      if (node->key1 != 0) {
        if (key > node->key1) {
          node->key2 = key;
        } else if (key < node->key1) {
          node->key2 = node->key1;
          node->key1 = key;
        }
      } else if (node->key2 != 0) {
        if (key < node->key2) {
          node->key1 = key;
        } else if (key > node->key2) {
          node->key1 = node->key2;
          node->key2 = key;
        }
      }
    } else if (node->keyCount() == 2) { // node is full
      if (key > node->key2) {
        node->right = new MultiNode();
        node->right->key1 = key;
      } else if (key < node->key1) {
        node->left = new MultiNode();
        node->left->key1 = key;
      } else {
        node->middle = new MultiNode();
        node->middle->key1 = key;
      }
    }
    return node;
  }
}

MultiNode *MultiWaySearchTree::removeKey(MultiNode *node, MultiNode *parent,
                                         int key) {
  if (node == NULL)
    return node;
  if (node->key1 != 0 && key < node->key1) {
    node->left = removeKey(node->left, node, key);
  } else if (node->key2 != 0 && key > node->key2) {
    node->right = removeKey(node->right, node, key);
  } else if (node->keyCount() == 2 && key > node->key1 && key < node->key2) {
    node->middle = removeKey(node->middle, node, key);
  } else {                // found key
    if (node->isleaf()) { // if node is leaf node
      if (node->keyCount() == 2) {
        if (node->key1 == key)
          node->key1 = 0;
        else if (node->key2 == key)
          node->key2 = 0;
      } else if (node->keyCount() == 1) {
        if (node->key1 == key)
          node->key1 = 0;
        else if (node->key2 == key)
          node->key2 = 0;
        node = NULL;
      }
    } else {                       // not leaf node
      if (node->keyCount() == 2) { // 1. full keys in the node
        if (node->key1 == key) {   // 1-1. remove key1 from the node
          if (node->middle != NULL) {
            MultiNode *smallest = smallestKey(node->middle);
            int replace = 0;
            if (smallest->key1 != 0) {
              replace = smallest->key1;
              smallest->key1 = 0;
            } else if (smallest->key2 != 0) {
              replace = smallest->key2;
              smallest->key2 = 0;
            }
            node->key1 = replace;
            node->middle = removeKey(node->middle, node, replace);
          } else if (node->left != NULL) {
            MultiNode *largest = largestKey(node->left);
            int replace = 0;
            if (largest->key2 != 0) {
              replace = largest->key2;
              largest->key2 = 0;
            } else if (largest->key1 != 0) {
              replace = largest->key1;
              largest->key1 = 0;
            }
            node->key1 = replace;
            node->left = removeKey(node->left, node, replace);
          } else {
            node->key1 = 0;
          }
        } else if (node->key2 == key) { // 1-2. remove key2 from the node
          if (node->right != NULL) {
            MultiNode *smallest = smallestKey(node->right);
            int replace = 0;
            if (smallest->key1 != 0) {
              replace = smallest->key1;
              smallest->key1 = 0;
            } else if (smallest->key2 != 0) {
              replace = smallest->key2;
              smallest->key2 = 0;
            }
            node->key2 = replace;
            node->right = removeKey(node->right, node, replace);
          } else if (node->middle != NULL) {
            MultiNode *largest = largestKey(node->middle);
            int replace = 0;
            if (largest->key2 != 0) {
              replace = largest->key2;
              largest->key2 = 0;
            } else if (largest->key1 != 0) {
              replace = largest->key1;
              largest->key1 = 0;
            }
            node->key2 = replace;
            node->middle = removeKey(node->middle, node, replace);
          } else {
            node->key2 = 0;
          }
        }
      } else if (node->keyCount() == 1) { // 2. one key in the node
        if (node->key1 == key) {          // 2-1. remove key1 from the node
          if (node->middle != NULL) {
            MultiNode *smallest = smallestKey(node->middle);
            int replace = smallest->key1;
            smallest->key1 = 0;
            if (replace == 0 && smallest->key2 != 0) {
              replace = smallest->key2;
              smallest->key2 = 0;
            }
            node->key1 = replace;
            node->middle = removeKey(node->middle, node, replace);
          } else if (node->left != NULL) {
            MultiNode *largest = largestKey(node->left);
            int replace = largest->key2;
            largest->key2 = 0;
            if (replace == 0 && largest->key1 != 0) {
              replace = largest->key1;
              largest->key1 = 0;
            }
            node->key1 = replace;
            node->left = removeKey(node->left, node, replace);
          } else if (node->right != NULL) {
            MultiNode *temp = NULL;
            temp = node->right;
            if (parent) {
              if (parent->left == node)
                parent->left = temp;
              else if (parent->middle == node)
                parent->middle = temp;
              else if (parent->right == node)
                parent->right = temp;
            }
            node = temp;
          }
        } else if (node->key2 == key) { // 2-2. remove key2 from the node
          if (node->right != NULL) {
            MultiNode *smallest = smallestKey(node->right);
            int replace = smallest->key1;
            smallest->key1 = 0;
            if (replace == 0 && smallest->key2 != 0) {
              replace = smallest->key2;
              smallest->key2 = 0;
            }
            node->key2 = replace;
            node->right = removeKey(node->right, node, replace);
          } else if (node->middle != NULL) {
            MultiNode *largest = largestKey(node->middle);
            int replace = largest->key2;
            largest->key2 = 0;
            if (replace == 0 && largest->key1 != 0) {
              replace = largest->key1;
              largest->key1 = 0;
            }
            node->key2 = replace;
            node->middle = removeKey(node->middle, node, replace);
          } else if (node->left != NULL) {
            MultiNode *temp = NULL;
            temp = node->left;
            if (parent) {
              if (parent->left == node)
                parent->left = temp;
              else if (parent->middle == node)
                parent->middle = temp;
              else if (parent->right == node)
                parent->right = temp;
            }
            node = temp;
          }
        }
      }
    }
    return node;
  }
  return node;
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////