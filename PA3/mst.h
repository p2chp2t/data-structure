#pragma once
#include <string>

using namespace std;

class MultiNode {
public:
  MultiNode()
      : key1(0), key2(0), height(0), left(NULL), middle(NULL), right(NULL) {}
  int key1;
  int key2;
  int height;
  MultiNode *left;
  MultiNode *middle;
  MultiNode *right;
  /* Add public members if required*/
  bool isleaf() { return left == NULL && middle == NULL && right == NULL; }
  int keyCount() {
    if (key1 != 0 && key2 != 0) // both keys have values
      return 2;
    else if (key1 != 0 || key2 != 0)
      return 1;
    else
      return 0;
  }
  string print_key() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    string keys = "";
    if (key1 != 0) {
      keys += to_string(key1);
      if (key2 != 0) {
        keys += " ";
        keys += to_string(key2);
      }
    } else if (key2 != 0) {
      keys += to_string(key2);
    }
    return keys;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
  };
};

class MultiWayTree {
public:
  MultiWayTree() { _root = NULL; };
  ~MultiWayTree() {
    delete[] _root;
    _root = NULL;
  };
  string preOrder();

protected:
  MultiNode *_root;

private:
  void _preOrder(string &output, MultiNode *cur);
};

class MultiWaySearchTree : public MultiWayTree {
public:
  MultiWaySearchTree(){};
  ~MultiWaySearchTree(){};

  int insert(int key);
  int remove(int key);

private:
  /////////////////////////////////////////////////////////
  //////  TODO: Add private members if required ///////////
  MultiNode *smallestKey(MultiNode *node);
  MultiNode *largestKey(MultiNode *node);
  bool existKey(MultiNode *node, int key);
  MultiNode *insertKey(MultiNode *node, int key);
  MultiNode *removeKey(MultiNode *node, MultiNode *parent, int key);
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
};
