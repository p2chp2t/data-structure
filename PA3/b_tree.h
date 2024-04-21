#pragma once
#include <string>

using namespace std;

class BNode {
public:
  int *keys;
  BNode **child;
  int n;
  bool isleaf;
  int m;

  BNode(int m, bool leaf);
  void insertKey(int key);
  void deleteKey(int key);
  void split(int i, BNode *node);
  void merge(int idx);
  void fill(int idx);
  BNode *search(int key);
  int searchKey(int key);
  string showKeys();
  void _postOrder(string &output);
};

class BTree {
public:
  /////////////////////////////////////////////////////////
  //////  TODO: Implement BTree class, Add public members if required
  //////////////

  BTree(int m) {
    _m = m;
    _root = NULL;
  };
  ~BTree() {
    delete[] _root;
    _root = NULL;
  };

  BNode *_root;
  int _m;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////

  int has_elem(int key);
  int insert_elem(int key);
  int delete_elem(int key);
  string postOrder();

private:
  /////////////////////////////////////////////////////////
  //////  TODO: Add private members if required ///////////

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
};
