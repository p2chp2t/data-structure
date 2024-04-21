#include "b_tree.h"
#include <iostream>
#include <string>

using namespace std;

/*  Write your codes for other b_tree functions  */
BNode::BNode(int m1, bool leaf) {
  isleaf = leaf;
  keys = new int[m1 - 1];
  for (int i = 0; i < m1 - 1; i++)
    keys[i] = 0;
  child = new BNode *[m1];
  for (int i = 0; i < m1; i++) {
    child[i] = NULL;
  }
  n = 0;
  m = m1;
}

BNode *BNode::search(int key) {
  int i = 0;
  while (i < n && key > keys[i])
    i++;
  if (keys[i] == key)
    return this;
  if (isleaf == true)
    return NULL;
  return child[i]->search(key);
}

int BNode::searchKey(int key) {
  int i = 0;
  while (i < n && keys[i] < key)
    ++i;
  return i;
}

void BNode::insertKey(int key) {
  int i = n - 1;
  if (isleaf == true) {
    while (i >= 0 && keys[i] > key) {
      keys[i + 1] = keys[i];
      i--;
    }
    keys[i + 1] = key;
    n++;
  } else {
    while (i >= 0 && keys[i] > key)
      i--;
    if (child[i + 1]->n == (m - 1)) {
      split(i + 1, child[i + 1]);
      if (keys[i + 1] < key)
        i++;
    }
    child[i + 1]->insertKey(key);
  }
}

void BNode::split(int i, BNode *node) {
  BNode *newNode = new BNode(node->m, node->isleaf);
  int med = (m - 1) / 2;

  if (m % 2 == 0) {
    // Even-order B-tree
    newNode->n = med;
    for (int j = 0; j < med; ++j) {
      newNode->keys[j] = node->keys[j + med + 1];
    }
    if (node->isleaf == false) {
      for (int j = 0; j < med + 1; ++j) {
        newNode->child[j] = node->child[j + med + 1];
      }
    }
  } else {
    // Odd-order B-tree
    newNode->n = med - 1;
    for (int j = 0; j <= med; ++j) {
      newNode->keys[j] = node->keys[j + med + 1];
    }
    if (node->isleaf == false) {
      for (int j = 0; j <= med + 1; ++j) {
        newNode->child[j] = node->child[j + med + 1];
      }
    }
  }
  node->n = med;
  for (int j = n; j > i; j--) {
    child[j + 1] = child[j];
  }
  child[i + 1] = newNode;
  for (int j = n - 1; j >= i; j--) {
    keys[j + 1] = keys[j];
  }
  keys[i] = node->keys[med];
  n++;
}

void BNode::merge(int idx) {
  BNode *cnode = child[idx];
  BNode *snode = child[idx + 1];
  int med = 0;
  if (m % 2 == 0)
    med = m / 2;
  else
    med = (m - 1) / 2;
  cnode->keys[med - 1] = keys[idx];
  for (int i = 0; i < snode->n; ++i)
    cnode->keys[i + med] = snode->keys[i];
  if (cnode->isleaf == false) {
    for (int i = 0; i < snode->n; ++i)
      cnode->child[i + med] = snode->child[i];
  }
  for (int i = idx + 1; i < n; ++i)
    keys[i - 1] = keys[i];
  for (int i = idx + 2; i <= n; ++i)
    child[i - 1] = child[i];
  cnode->n += snode->n + 1;
  n--;
  delete snode;
  return;
}

void BNode::deleteKey(int key) {
  int idx = searchKey(key);
  int med = 0; // median value when overflow occurs
  if (m % 2 == 0)
    med = m / 2;
  else
    med = (m - 1) / 2;
  if (idx < n && keys[idx] == key) {
    if (isleaf) { // 1. leaf node
      for (int j = idx + 1; j < n; ++j)
        keys[j - 1] = keys[j];
      n--;
    } else { // 2. not leaf node
      int k = keys[idx];
      if (child[idx]->n >= med) {
        int prev = 0;
        BNode *cur = child[idx];
        while (cur->isleaf == false)
          cur = cur->child[cur->n];
        prev = cur->keys[cur->n - 1];
        keys[idx] = prev;
        child[idx]->deleteKey(prev);
      } else if (child[idx + 1]->n >= med) {
        int next = 0;
        BNode *cur = child[idx + 1];
        while (cur->isleaf == false)
          cur = cur->child[0];
        next = cur->keys[0];
        keys[idx] = next;
        child[idx + 1]->deleteKey(next);
      } else {
        merge(idx);
        child[idx]->deleteKey(key);
      }
    }
  } else {
    if (isleaf == true)
      return;
    bool flag = idx == n;
    if (child[idx]->n < med)
      fill(idx);
    if (flag && idx > n)
      child[idx - 1]->deleteKey(key);
    else
      child[idx]->deleteKey(key);
  }
  return;
}

void BNode::fill(int idx) {
  int med = 0;
  if (m % 2 == 0)
    med = m / 2;
  else
    med = (m - 1) / 2;
  if (idx != 0 && child[idx - 1]->n >= med) { // 1. borrow from previous node
    BNode *cnode = child[idx];
    BNode *snode = child[idx - 1];
    for (int i = cnode->n - 1; i >= 0; --i)
      cnode->keys[i + 1] = cnode->keys[i];
    if (cnode->isleaf == false) {
      for (int i = cnode->n; i >= 0; --i)
        cnode->child[i + 1] = cnode->child[i];
    }
    cnode->keys[0] = keys[idx + 1];
    if (cnode->isleaf == false)
      cnode->child[0] = snode->child[snode->n];
    keys[idx - 1] = snode->keys[snode->n - 1];
    cnode->n++;
    snode->n--;
  } else if (idx != n && child[idx + 1]->n >= med) { // 2. borrow from next
    BNode *cnode = child[idx];
    BNode *snode = child[idx + 1];
    cnode->keys[cnode->n] = keys[idx];
    if (cnode->isleaf == false)
      cnode->child[cnode->n - 1] = snode->child[0];
    keys[idx] = snode->keys[0];
    for (int i = 1; i < snode->n; ++i)
      snode->keys[i - 1] = snode->keys[i];
    if (snode->isleaf == false) {
      for (int i = 1; i <= snode->n; ++i)
        snode->child[i - 1] = snode->child[i];
    }
    cnode->n++;
    snode->n--;
  } else {
    if (idx != n)
      merge(idx);
    else
      merge(idx - 1);
  }
}

string BNode::showKeys() {
  string output = "";
  output += "[";
  int i;
  for (i = 0; i < n - 1; i++) {
    output += to_string(keys[i]);
    output += ", ";
  }
  output += to_string(keys[n - 1]);
  output += "]";
  return output;
}

void BNode::_postOrder(string &output) {
  int i;
  for (i = 0; i < n; i++) {
    if (isleaf == false)
      child[i]->_postOrder(output);
  }
  if (isleaf == false)
    child[i]->_postOrder(output);
  output += showKeys();
  output += " ";
  return;
}
///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

string BTree::postOrder() {
  /*  Write your codes for b_tree functions  */
  string output;
  if (_root != NULL) {
    _root->_postOrder(output);
  }
  if (!output.empty())
    output.pop_back();
  return output;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

int BTree::has_elem(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  if (_root == NULL) { // no elements
    return 1;
  }
  BNode *target = _root->search(key);
  if (target == NULL)
    return 1;
  return 0;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

int BTree::insert_elem(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  if (_root == NULL) {
    _root = new BNode(_m, true);
    _root->keys[0] = key;
    _root->n = 1;
  } else {
    if (_root->n == _m - 1) {
      BNode *node1 = new BNode(_m, false);
      node1->child[0] = _root;
      node1->split(0, _root);
      int i = 0;
      if (node1->keys[0] < key)
        i++;
      node1->child[i]->insertKey(key);
      _root = node1;
    } else
      _root->insertKey(key);
  }

  return 0;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

int BTree::delete_elem(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  if (_root->search(key) == NULL || _root == NULL)
    return -1;
  else
    _root->deleteKey(key);
  return 0;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}